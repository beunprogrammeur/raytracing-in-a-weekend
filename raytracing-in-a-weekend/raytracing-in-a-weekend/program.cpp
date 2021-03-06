#include "program.h"

#include <iostream>
#include "hittable_list.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"
#include "random.h"
#include <filesystem>
#include <fstream>
#include "io.h"
#include "material.h"

hittable_list random_scene() {
	using namespace std;
	
	hittable_list world;

	auto ground_material = make_shared<lambertian_material>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian_material>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal_material>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<dielectric_material>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric_material>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian_material>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal_material>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}


color ray_color(const ray& r, const hittable& world, int depth) {
	hit_record rec;
	
	if (depth <= 0) return color::zero();

	if (world.hit(r, 0.001, infinity, rec)) {
		ray scattered;
		color attenuation;
		
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * ray_color(scattered, world, depth - 1);
		}
		
		return color::zero();
	}

	vec3 unit_direction = r.direction().unit();
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1, 1, 1) + t * color(0.5, 0.7, 1.0);
}

int main()
{
	// io
	const std::string output_folder = ".\\output";
	const std::string file = "image";
	const std::string extension = "ppm";

	std::filesystem::create_directory(std::filesystem::path(output_folder));

	auto path = generate_file_path(output_folder, file, extension);
	std::cout << "generated path: " << path << std::endl;
	std::ofstream output_file;
	output_file.open(path);
	if (!output_file.is_open()) {
		std::cerr << "failed to open file: " << path << std::endl;
		return 1;
	}

	// image
	constexpr auto aspect_ratio = 16.0 / 9.0;
	constexpr long image_width = 1200;
	constexpr long image_height = static_cast<long>(image_width / aspect_ratio);
	constexpr long samples_per_pixel = 500;
	constexpr long max_depth = 50;

	// world
	hittable_list world = random_scene();
	
	// camera 
	point3 lookfrom(13, 2, 3);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;

	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	// render

	output_file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--)
	{
		std::cerr << "scanline: " << image_height - j << ' ' << std::endl << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			color pixel = color::zero();

			for (int s = 0; s < samples_per_pixel; ++s) {

				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel += ray_color(r, world, max_depth);
			}	
			write_color(output_file, pixel, samples_per_pixel);
		}
	}

	std::cerr << "done." << std::endl;
	output_file.close();
	system(path.c_str());
	return 0;
}

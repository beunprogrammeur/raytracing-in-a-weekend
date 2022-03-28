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
using namespace std;




color ray_color(const ray& r, const hittable& world, int depth) {
	hit_record rec;
	
	if (depth <= 0) return color::zero();

	if (world.hit(r, 0.001, infinity, rec)) {
		point3 target = rec.p + rec.normal + vec3::random_in_unit_sphere().unit();
		return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
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
	constexpr long image_width = 400;
	constexpr long image_height = static_cast<long>(image_width / aspect_ratio);
	constexpr long samples_per_pixel = 100;
	constexpr long max_depth = 50;

	// world
	hittable_list world;
	world.add(std::make_shared<sphere>(point3(0, 0.1, -1), 0.5));
	world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));


	// camera
	camera cam;



	// render

	output_file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--)
	{
		if (j % 10 == 0) std::cerr << "scanline: " << image_height - j << ' ' << std::endl << std::flush;

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

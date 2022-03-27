#include <iostream>
#include "color.h"
#include "ray.h"
#include "vec3.h"

using namespace std;

color ray_color(const ray& r) {
	vec3 unit_direction = r.direction().unit();
	auto t = 0.5 * (unit_direction.y() + 1);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + (t * color(0.5, 0.7, 1.0));
}


int main()
{
	// image
	constexpr auto aspect_ratio = 16.0 / 9.0;
	constexpr long image_width = 400;
	constexpr long image_height = static_cast<long>(image_width / aspect_ratio);

	// camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto low_left_corner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focal_length);



	// render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--)
	{
		std::cerr << "scanline: " << image_height - j << ' ' << std::endl << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);
			ray r(origin, low_left_corner + u * horizontal + v * vertical - origin);

			//color pixel((double)i / (image_width - 1), (double)j / (image_height - 1), 0.25);
			color pixel = ray_color(r);
			write_color(std::cout, pixel);
		}
	}

	std::cerr << "done." << std::endl;

	return 0;
}

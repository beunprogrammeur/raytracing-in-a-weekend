#pragma once

#include "vec3.h"

void write_color(std::ostream& out, const color& pixel_color, int samples_per_pixel) {

	auto scale = 1.0 / samples_per_pixel;
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	r = clamp(r, 0, 0.999);
	g = clamp(g, 0, 0.999);
	b = clamp(b, 0, 0.999);


	// Write the translated [0,255] value of each color component.
	out << static_cast<int>(256 * r) << ' '
		<< static_cast<int>(256 * g) << ' '
		<< static_cast<int>(256 * b) << '\n';
}
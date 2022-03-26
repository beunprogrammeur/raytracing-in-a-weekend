#include <iostream>
#include "color.h"
#include "vec3.h"
using namespace std;

int main()
{
	constexpr long image_width = 256;
	constexpr long image_height = 256;

	// render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--)
	{
		std::cerr << "scanline: " << image_height - j << ' ' << std::endl << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			color pixel((double)i / (image_width - 1), (double)j / (image_height - 1), 0.25);
			write_color(std::cout, pixel);
		}
	}

	std::cerr << "done." << std::endl;

	return 0;
}

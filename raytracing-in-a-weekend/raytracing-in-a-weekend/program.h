#pragma once

#include <cmath>
#include <limits>
#include <memory>

#include "ray.h"
#include "vec3.h"

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}
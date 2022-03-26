#include "vec3.h"

vec3 vec3::unit() {
	return *this / length();
}

vec3 vec3::cross(const vec3& other)
{
	return vec3(e[1] * other.e[2] - e[2] * other.e[1],
				e[2] * other.e[0] - e[0] * other.e[2],
				e[0] * other.e[1] - e[1] * other.e[0]);
}

double vec3::dot(const vec3& other) {
	return e[0] * other.e[0]
	     + e[1] * other.e[1]
	     + e[2] * other.e[2];
}

double length() const {
	return sqrt(length_squared());
}

double length_squared() const {
	return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
}
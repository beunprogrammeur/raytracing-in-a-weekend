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

double vec3::dot(const vec3& other) const {
	return e[0] * other.e[0]
	     + e[1] * other.e[1]
	     + e[2] * other.e[2];
}

double vec3::dot() const {
	return dot(*this);
}

double vec3::length() const {
	return sqrt(length_squared());
}

double vec3::length_squared() const {
	return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
}

vec3 vec3::reflect(const vec3& n) const { 
	return (*this) - (2 * dot(n) * n); 
}
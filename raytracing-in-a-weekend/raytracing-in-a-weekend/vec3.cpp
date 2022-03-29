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

vec3 vec3::refract(const vec3& n, double etai_over_etat) const {
	auto cos_theta = fmin((-*this).dot(n), 1.0);
	vec3 r_out_perp = etai_over_etat * (*this + cos_theta * n);
	vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}
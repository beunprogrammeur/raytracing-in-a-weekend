#pragma once
#include <memory>
#include "ray.h"

class material;

struct hit_record {
	point3 p;
	vec3 normal;
	std::shared_ptr<material> mat_ptr;
	
	double t;
	bool front_face;

	hit_record() : p(point3::zero()), normal(vec3::zero()), mat_ptr(nullptr), t(0), front_face(false) {}

	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = r.direction().dot(outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
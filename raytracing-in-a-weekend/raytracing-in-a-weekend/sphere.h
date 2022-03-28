#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
private:
	point3 m_center;
	double m_radius;
public:
	sphere() {}
	sphere(point3 center, double radius) : m_center(center), m_radius(radius) {}
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

};
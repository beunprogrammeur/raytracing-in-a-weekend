#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
private:
	point3 m_center;
	double m_radius;
	std::shared_ptr<material> m_material;
public:
	sphere() : m_center(point3::zero()), m_radius(0), m_material(nullptr) {}
	sphere(point3 center, double radius, std::shared_ptr<material> material) : m_center(center), m_radius(radius), m_material(material) {}
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

};
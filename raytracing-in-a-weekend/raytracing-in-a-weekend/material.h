#pragma once
#include "vec3.h"
#include "ray.h"
struct hit_record;

class material {
public:
	virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};


class lambertian_material : public material {
private:
	color m_albedo;

public:
	lambertian_material(color albedo) : m_albedo(albedo) {}

	virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const {
		auto scatter_direction = rec.normal + vec3::random();

		// catch degenerate scatter direction 
		if (scatter_direction.near_zero()) {
			scatter_direction = rec.normal;
		}

		scattered = ray(rec.p, scatter_direction);
		attenuation = m_albedo;
		return true;
	}
};

class metal_material : public material {
private:
	color m_albedo;
	double m_fuzz;
public:
	metal_material(color albedo, double fuzz) : m_albedo(albedo), m_fuzz(fuzz) {}

	virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const {
		vec3 reflected = r.direction().unit().reflect(rec.normal);
		scattered = ray(rec.p, reflected + m_fuzz * vec3::random_in_unit_sphere());
		attenuation = m_albedo;
		return scattered.direction().dot(rec.normal) > 0;
	}
};
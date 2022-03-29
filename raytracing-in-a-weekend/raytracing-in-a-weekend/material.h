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

class dielectric_material : public material {
private:
	double m_refraction_index;

public:
	dielectric_material(double refraction_index) : m_refraction_index(refraction_index) {}

	virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const {
		attenuation = color(1, 1, 1);
		double refraction_ratio = rec.front_face ? (1.0 / m_refraction_index) : m_refraction_index;

		vec3 unit_direction = r.direction().unit();
		double cos_theta = fmin((-unit_direction).dot(rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
		vec3 direction;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
			direction = unit_direction.reflect(rec.normal);
		}
		else {
			direction = unit_direction.refract(rec.normal, refraction_ratio);
		}

		scattered = ray(rec.p, direction);

		return true;
	}

private:
	static double reflectance(double cosine, double ref_idx) {
		// schlick approximation 
		auto r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1.0 - r0) * pow(1 - cosine, 5);
	}
};
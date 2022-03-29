#pragma once

#include "vec3.h"
#include "ray.h"

class camera {
private:
	point3 m_origin;
	point3 m_lower_left_corner;
	vec3 m_horizontal;
	vec3 m_vertical;
	vec3 m_u;
	vec3 m_v;
	vec3 m_w;
	double m_lens_radius;

public:
	camera(point3 look_from, point3 look_at, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_distance);
	ray get_ray(double u, double v) const;
};
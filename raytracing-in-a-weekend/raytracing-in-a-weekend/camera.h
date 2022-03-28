#pragma once

#include "vec3.h"
#include "ray.h"

class camera {
private:
	point3 m_origin;
	point3 m_lower_left_corner;
	vec3 m_horizontal;
	vec3 m_vertical;

public:
	camera();
	ray get_ray(double u, double v) const;
};
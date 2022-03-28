#include "camera.h"

camera::camera() {
	auto aspect_ratio = 16.0 / 9.0;
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	m_origin = vec3::zero();
	m_horizontal = vec3(viewport_width, 0, 0);
	m_vertical = vec3(0, viewport_height, 0);
	m_lower_left_corner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - vec3(0, 0, focal_length);
}

ray camera::get_ray(double u, double v) const {
	return ray(m_origin, m_lower_left_corner + (u * m_horizontal) + (v * m_vertical) - m_origin);
}
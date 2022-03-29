#include "camera.h"
#include "program.h"
camera::camera(point3 look_from, point3 look_at, vec3 vup, double vfov, double aspect_ratio) {
	auto theta = degrees_to_radians(vfov);
	auto h = tan(theta / 2);
	auto viewport_height = 2.0 * h;
	auto viewport_width = aspect_ratio * viewport_height;

	auto w = (look_from - look_at).unit();
	auto u = vup.cross(w).unit();
	auto v = w.cross(u);

	m_origin = look_from;
	m_horizontal = viewport_width * u;
	m_vertical = viewport_height * v;
	m_lower_left_corner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - w;
}

ray camera::get_ray(double s, double t) const {
	return ray(m_origin, m_lower_left_corner + (s * m_horizontal) + (t * m_vertical) - m_origin);
}
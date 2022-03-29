#include "camera.h"
#include "program.h"
camera::camera(point3 look_from, point3 look_at, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_distance) {
	auto theta = degrees_to_radians(vfov);
	auto h = tan(theta / 2);
	auto viewport_height = 2.0 * h;
	auto viewport_width = aspect_ratio * viewport_height;

	m_w = (look_from - look_at).unit();
	m_u = vup.cross(m_w).unit();
	m_v = m_w.cross(m_u);

	m_origin = look_from;
	m_horizontal = focus_distance * viewport_width * m_u;
	m_vertical = focus_distance * viewport_height * m_v;
	m_lower_left_corner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - (focus_distance * m_w);

	m_lens_radius = aperture / 2.0;
}

ray camera::get_ray(double s, double t) const {
	vec3 rd = m_lens_radius * vec3::random_in_unit_disk();
	vec3 offset = m_u * rd.x() + m_v * rd.y();

	return ray(m_origin + offset, m_lower_left_corner + (s * m_horizontal) + (t * m_vertical) - m_origin - offset);
}
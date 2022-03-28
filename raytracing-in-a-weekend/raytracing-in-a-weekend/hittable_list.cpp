#include "hittable_list.h"

void hittable_list::clear() {
	m_objects.clear();
}
void hittable_list::add(std::shared_ptr<hittable> object) {
	m_objects.push_back(object);
}

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : m_objects) {
		if (object->hit(r, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}
#pragma once
#include "hittable.h"
#include <memory>
#include <vector>

class hittable_list : public hittable {
private:
	std::vector<std::shared_ptr<hittable>> m_objects;

public:
	hittable_list() {}
	hittable_list(std::shared_ptr<hittable> object) { add(object); }

	void clear();
	void add(std::shared_ptr<hittable> object);

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};
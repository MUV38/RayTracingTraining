#ifndef HITABLE_H
#define	HITABLE_H

#include "ray.h"
#include "aabb.h"

class material;

struct hit_record{
	double		t;
	vec3		p;
	vec3		normal;
	material*   mat_ptr;
    float       u, v;

    hit_record()
        : t (-1)
        , p(0, 0, 0)
        , mat_ptr(nullptr)
        , u(0)
        , v(0)
    {}
};

class hitable{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
    virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;
};

#endif // !HITABLE_H

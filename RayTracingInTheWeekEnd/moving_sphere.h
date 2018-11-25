#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "hitable.h"

class moving_sphere : public hitable{
public:
    moving_sphere(){}
    moving_sphere(vec3 cen0, vec3 cen1, float t0, float t1, double r, material* mat) 
        : center0(cen0) 
        , center1(cen1)
        , time0(t0)
        , time1(t1)
        , radius(r)
        , material(mat)
    {}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& box) const override;
    vec3 center(float time) const;

	vec3	    center0, center1;
    float       time0, time1;
	double	    radius;
    material*   material;
};

bool moving_sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const{
	vec3 oc = r.origin() - center(r.time());
	double a = dot(r.direction(), r.direction());
	double b = 2.0 * dot(oc, r.direction());
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b*b - 4*a*c;
	if(discriminant > 0){
		double temp = (-b - sqrt(b*b-4*a*c)) / (2*a);
		if(temp < t_max && temp > t_min){
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = material;
			return true;
		}
		temp = (-b + sqrt(b*b-4*a*c)) / (2*a);
		if(temp < t_max && temp > t_min){
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = material;
            return true;
		}
	}

	return false;
}

vec3 moving_sphere::center(float time) const 
{
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::bounding_box(float t0, float t1, aabb& box) const
{
    aabb box0(center(t0) - vec3(radius, radius, radius), center(t0) + vec3(radius, radius, radius));
    aabb box1(center(t1) - vec3(radius, radius, radius), center(t1) + vec3(radius, radius, radius));
    box = surrounding_box(box0, box1);
    return true;
}

#endif // !MOVING_SPHERE_H

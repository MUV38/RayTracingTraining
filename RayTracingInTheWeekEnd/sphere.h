#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class sphere : public hitable{
public:
	sphere(){}
	sphere(vec3 cen, double r, material* mat) : center(cen), radius(r), material(mat){}
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& box) const override;

	vec3	    center;
	double	    radius;
    material*   material;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const{
	vec3 oc = r.origin() - center;
	double a = dot(r.direction(), r.direction());
	double b = 2.0 * dot(oc, r.direction());
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b*b - 4*a*c;
	if(discriminant > 0){
		double temp = (-b - sqrt(b*b-4*a*c)) / (2*a);
		if(temp < t_max && temp > t_min){
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
			return true;
		}
		temp = (-b + sqrt(b*b-4*a*c)) / (2*a);
		if(temp < t_max && temp > t_min){
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
		}
	}

	return false;
}

bool sphere::bounding_box(float t0, float t1, aabb& box) const
{
    box = aabb(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
    return true;
}

#endif // !SPHERE_H

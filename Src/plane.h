#ifndef _PLANE_H_
#define	_PLANE_H_

#include "object.h"

/**
* @brief –³ŒÀ•½–Ê‚Ì’è‹`
*/
class Plane : public Object
{
public:
	Plane()
	: normal(0, 1, 0) 
	{}

	~Plane() {}

public:
	bool Hit(ShadeRecord* sr, double* tmin, double t_max, Vec* normal, const Ray& ray) override
	{
		this->normal = normalize(this->normal);

		double t = (dot(pos - ray.origin, this->normal)) / (dot(ray.direction, this->normal));

		if (t >= 0 && t < t_max) {
			*tmin = t;
			*normal = this->normal;
			sr->hit_point = ray.origin + t * ray.direction;
			return true;
		}

		*tmin = 1000;
		return false;
	}
public:
	Vec pos;		// ˆÊ’u
	Vec normal;	// –@ü
};

#endif // !_PLANE_H_

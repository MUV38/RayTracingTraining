#ifndef _PLANE_H_
#define	_PLANE_H_

#include "object.h"
#include "material.h"

/**
* @brief �������ʂ̒�`
*/
class Plane : public Object
{
public:
	Plane(Material* material)
		: Object(material)
		, normal(0, 1, 0) 
	{}

	~Plane() {}

public:
	bool Hit(ShadeRecord* sr, double* tmin, Vec* normal, const Ray& ray) override
	{
		this->normal = normalize(this->normal);

		double t = (dot(pos - ray.origin, this->normal)) / (dot(ray.direction, this->normal));

		if (t >= 0) {
			*tmin = t;
			*normal = this->normal;
			sr->hit_point = ray.origin + t * ray.direction;
			return true;
		}

		*tmin = 1000;
		return false;
	}
public:
	Vec pos;		// �ʒu
	Vec normal;	// �@��
};

#endif // !_PLANE_H_

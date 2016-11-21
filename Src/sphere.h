#ifndef _SPHERE_H_
#define	_SPHERE_H_

#include "object.h"

class Sphere : public Object
{
public:
	Sphere()
	: radius(1)
	, pos(0, 0, 0)
	{}

	~Sphere(){}
	
public:
	bool Hit(ShadeRecord* sr, double* tmin, double t_max, Vec* normal, const Ray& ray) override
	{
		Vec s = ray.origin - pos;

		double A = ray.direction.length_squared(); // ���C�̕����͐��K������Ă���̂ŏ�ɂP�Ȃ肻���Ȃ̂ŁA�P�ŌŒ肵�Ă���������
		double B = 2.0f * dot(s, ray.direction);
		double C = s.length_squared() - (radius * radius);

		double D = B * B - 4.0 * A * C;

		if (D < 0) { return false; }

		double E = sqrt(D);
		double denom = 2.0f * A;

		double t = 0;

		// -�̏ꍇ
		t = (-B - E) / denom;
		if (t >= 0 && t < t_max) {
			*tmin = t;
			*normal = normalize((s + t * ray.direction) / radius);
			sr->hit_point = ray.origin + t * ray.direction;
			return true;
		}

		// +�̏ꍇ
		t = (-B + E) / denom;
		if (t >= 0 && t < t_max) {
			*tmin = t;
			*normal = normalize((s + t * ray.direction) / radius);
			sr->hit_point = ray.origin + t * ray.direction;
			return true;
		}

		*tmin = 1000;
		return false;
	}

public:
	double		radius;	// ���a
	Vec			pos;	// ���S�_
};


#endif // !_SPHERE_H_

#ifndef _SPHERE_H_
#define	_SPHERE_H_

#include "object.h"
#include "material.h"

class Sphere : public Object
{
public:
	Sphere(Material* material)
		: Object(material)
		, radius(1)
		, pos(0, 0, 0)
	{}

	~Sphere(){}
	
public:
	bool Hit(ShadeRecord* sr, double* tmin, Vec* normal, const Ray& ray) override
	{
#if 1
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
		if (t >= 0) {
			*tmin = t;
			*normal = normalize((s + t * ray.direction) / radius);
			sr->hit_point = ray.origin + t * ray.direction;
			return true;
		}

		// +�̏ꍇ
		t = (-B + E) / denom;
		if (t >= 0) {
			*tmin = t;
			*normal = normalize((s + t * ray.direction) / radius);
			sr->hit_point = ray.origin + t * ray.direction;
			return true;
		}

		*tmin = 1000;
		return false;
#else 
		// ���Ȍ����̔���p�萔�B
		const double kEPS = 1e-6;

		const Vec o_to_p = this->pos - ray.origin;
		const double b = dot(o_to_p, ray.direction);
		const double c = b * b - dot(o_to_p, o_to_p) + this->radius * this->radius;

		if (c < 0.0)
			return false;

		const double sqrt_c = sqrt(c);
		const double t1 = b - sqrt_c, t2 = b + sqrt_c;

		// ������������������������Ȃ��Ƃ���i���Ȍ���������邽�߁j�B
		if (t1 < kEPS && t2 < kEPS)
			return false;

		// ��������Ƃ��͓�_�ȏ�Ō�������B�i�ڂ���ꍇ�͈�_�j
		// �߂����������_�Ƃ���B�܂��A���l�̏ꍇ�̓��C�̋t�����Ō������Ă邽�ߌ������Ă��Ȃ��Ƃ���B
		if (t1 > kEPS) {
			*tmin = t1;
		}
		else {
			*tmin = t2;
		}

		sr->hit_point = ray.origin + (*tmin) * ray.direction;
		*normal = normalize(sr->hit_point - this->pos);
		return true;

#endif
	}

public:
	double		radius;	// ���a
	Vec			pos;	// ���S�_
};


#endif // !_SPHERE_H_

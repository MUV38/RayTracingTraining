#include "my_sphere.h"

using namespace edupt;

namespace My{
	// ���C�Ƃ̌�������
	bool Sphere::Hit(ShadeRec* sr, double* tmin, double t_max, edupt::Vec* normal, const Ray& ray){
		Vec s = ray.origin - pos;

		double A = ray.direction.length_squared(); // ���C�̕����͐��K������Ă���̂ŏ�ɂP�Ȃ肻���Ȃ̂ŁA�P�ŌŒ肵�Ă���������
		double B = 2.0f * dot(s, ray.direction);
		double C = s.length_squared() - (radius * radius);

		double D = B * B - 4.0 * A * C;

		if(D < 0) { return false; }

		double E = sqrt(D);
		double denom = 2.0f * A;

		double t = 0;

		// -�̏ꍇ
		t = (-B - E) / denom;
		if(t >= 0 && t < t_max){ 
			*tmin = t;
			*normal = normalize((s + t * ray.direction) / radius);
			sr->hit_point = ray.origin + t * ray.direction;
			return true;
		}

		// +�̏ꍇ
		t = (-B + E) / denom;
		if(t >= 0 && t < t_max){
			*tmin = t;
			*normal = normalize((s + t * ray.direction) / radius);
			sr->hit_point = ray.origin + t * ray.direction;
			return true;
		}

		*tmin = 1000;
		return false;
	}
}
/**
* @file		my_intersect.h
* @brief	�Փ˔���̒�`
* @author	Toru Miyawaki
*/

#include "my_intersect.h"
#include "../vec.h"

using namespace edupt;

namespace My{
	// ���ƃ��C�̏Փ˔���
	bool IntersectSphere(const Ray& ray, const Sphere& sphere){
		Vec s = ray.origin - sphere.pos;

		double A = ray.direction.length_squared();
		double B = 2.0f * dot(s, ray.direction);
		double C = s.length_squared() - (sphere.radius * sphere.radius);

		double D = B * B - 4.0 * A * C;

		if(D < 0) { return false; }

		double E = sqrt(D);
		double denom = 2.0f * A;

		double t = 0;

		// -�̏ꍇ
		t = (-B - E) / denom;
		if(t >= 0){ return true; }

		// +�̏ꍇ
		t = (-B + E) / denom;
		if(t >= 0){ return true; }

		return false;
	}
};
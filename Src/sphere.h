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

		double A = ray.direction.length_squared(); // レイの方向は正規化されているので常に１なりそうなので、１で固定してもいいかも
		double B = 2.0f * dot(s, ray.direction);
		double C = s.length_squared() - (radius * radius);

		double D = B * B - 4.0 * A * C;

		if (D < 0) { return false; }

		double E = sqrt(D);
		double denom = 2.0f * A;

		double t = 0;

		// -の場合
		t = (-B - E) / denom;
		if (t >= 0) {
			*tmin = t;
			*normal = normalize((s + t * ray.direction) / radius);
			sr->hit_point = ray.origin + t * ray.direction;
			return true;
		}

		// +の場合
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
		// 自己交差の判定用定数。
		const double kEPS = 1e-6;

		const Vec o_to_p = this->pos - ray.origin;
		const double b = dot(o_to_p, ray.direction);
		const double c = b * b - dot(o_to_p, o_to_p) + this->radius * this->radius;

		if (c < 0.0)
			return false;

		const double sqrt_c = sqrt(c);
		const double t1 = b - sqrt_c, t2 = b + sqrt_c;

		// 微小距離内だったら交差しないとする（自己交差を避けるため）。
		if (t1 < kEPS && t2 < kEPS)
			return false;

		// 交差するときは二点以上で交差する。（接する場合は一点）
		// 近い方を交差点とする。また、負値の場合はレイの逆方向で交差してるため交差していないとする。
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
	double		radius;	// 半径
	Vec			pos;	// 中心点
};


#endif // !_SPHERE_H_

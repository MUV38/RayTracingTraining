#ifndef _MONTE_CARLO_RAY_TRACER_H_
#define	_MONTE_CARLO_RAY_TRACER_H_

#include "tracer.h"

class MonteCarloRayTracer : public Tracer
{
public:
	MonteCarloRayTracer(World* world) : Tracer(world){}
	~MonteCarloRayTracer(){}

public:
	/**
	* @brief ���C�̒ǐ�
	* @param [in] ray ���C
	* @return �`��F
	*/
	Color TraceRay(const Ray& ray) override
	{
		ShadeRecord sr;
		m_world->HitObjects(ray, &sr);

		// ���C���������Ă��邩
		if(sr.is_intersect)
		{
			return sr.material.albedo;
		}
		else
		{
			Vec unit_direction = normalize(ray.direction);
			double t = 0.5 * (unit_direction.y + 1.0);
			return (1.0 - t) * Vec(1.0, 1.0, 1.0) + t * Vec(0.5, 0.7, 1.0);
		}
	}

private:

};


#endif // !_MONTE_CARLO_RAY_TRACER_H_

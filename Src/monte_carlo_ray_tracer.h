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
	* @brief レイの追跡
	* @param [in] ray レイ
	* @return 描画色
	*/
	Color TraceRay(const Ray& ray) override
	{
		ShadeRecord sr;
		m_world->HitObjects(ray, &sr);

		// レイが交差しているか
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

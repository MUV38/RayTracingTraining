#include "TestTracer.h"
#include "../vec.h"

using namespace edupt;

void srand48(long int seedval) {
}
double drand48(void) {
	return rand() / (double)RAND_MAX;
}

Vec random_in_unit_sphere() {
	Vec p;
	do {
		p = 2.0 * Vec(drand48(), drand48(), drand48()) - Vec(1, 1, 1);
	} while (p.length_squared() >= 1.0);
	return p;
}

namespace My{
	TestTracer::TestTracer(World* world)
		: Tracer(world)
		, m_bounsNum(0)
	{

	}

	TestTracer::~TestTracer(){
	}

	// ƒŒƒC‚Ì’ÇÕ
	edupt::Color TestTracer::TraceRay(const Ray& ray, double t_max){
		ShadeRec sr;
		m_world->HitObjects(ray, t_max, &sr);

		// ƒŒƒC‚ªŒð·‚µ‚Ä‚¢‚é‚©
		if(sr.is_intesect){
			//Vec lightDir = normalize(Vec(0, -1, 0) * -1);
			//float intensity = dot(sr.normal, lightDir);
			//intensity = intensity >= 0 ? intensity : 0;

			//return sr.color * intensity;
			//return sr.color;
			//return sr.normal + 1.0f * 0.5f;

			m_bounsNum++;

			Vec target = sr.hit_point + sr.normal + random_in_unit_sphere();
			Ray nextRay;
			nextRay.origin = sr.hit_point;
			nextRay.direction = normalize(target - sr.hit_point);
			return 0.5 * TraceRay(nextRay, t_max);
		}else{
			m_bounsNum = 0;
			Vec unit_direction = normalize(ray.direction);
			double t = 0.5 * (unit_direction.y + 1.0);
			return (1.0 - t) * Vec(1.0, 1.0, 1.0) + t * Vec(0.5, 0.7, 1.0);
		}
	}
}
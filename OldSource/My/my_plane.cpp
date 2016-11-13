#include "my_plane.h"

using namespace edupt;

namespace My{
	bool Plane::Hit(ShadeRec* sr, double* tmin, double t_max, edupt::Vec* normal, const Ray& ray){
		this->normal = normalize(this->normal);

		double t = (dot(pos - ray.origin, this->normal)) / (dot(ray.direction, this->normal));

		if(t >= 0 && t < t_max){
			*tmin = t;
			*normal = this->normal;
			sr->hit_point = ray.origin + t * ray.direction;
			return true;
		}

		*tmin = 1000;
		return false;
	}
}
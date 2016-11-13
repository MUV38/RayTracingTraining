/**
* @file		my_intersect.h
* @brief	Õ“Ë”»’è‚Ì’è‹`
* @author	Toru Miyawaki
*/

#ifndef MY_INTERSECT_H
#define MY_INTERSECT_H

#include "my_ray.h"
#include "my_sphere.h"

namespace My{
	/**
	* @brief ‹…‚ÆƒŒƒC‚ÌÕ“Ë”»’è
	* @param [in] ray		ƒŒƒC
	* @param [in] sphere	‹…
	* @return Õ“Ë‚µ‚½‚©
	*/
	bool IntersectSphere(const Ray& ray, const Sphere& sphere);
};

#endif // !MY_INTERSECT_H

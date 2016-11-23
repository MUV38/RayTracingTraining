#ifndef _RAY_H_
#define	_RAY_H_

#include "vec.h"

/**
* @brief ƒŒƒC‚Ì’è‹`
*/
struct Ray{
	Ray(){}
	Ray(const Vec& origin, const Vec& direction)
		: origin(origin)
		, direction(direction)
	{}

	Vec	origin;
	Vec	direction;
};

#endif // !_RAY_H_



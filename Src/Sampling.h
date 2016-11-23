#ifndef _SAMPLING_H_
#define _SAMPLING_H_

#include "vec.h"
#include "random.h"
#include "constant.h"

namespace Sampling
{
	static Vec UniformHemisphereSurface(Random& random, const Vec& normal, const Vec& tangent, const Vec& binormal)
	{
		const double tz = random.next(0.0, 1.0);
		const double phi = random.next(0.0, 2.0 * PI);
		const double k = sqrt(1.0 - tz * tz);
		const double tx = k * cos(phi);
		const double ty = k * sin(phi);

		return tz * normal + tx * tangent + ty * binormal;
	}
}

#endif // !_SAMPLING_H_

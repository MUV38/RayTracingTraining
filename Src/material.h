#ifndef _MATERIAL_H_
#define	_MATERIAL_H_

#include "vec.h"

typedef Vec Color;

struct Material
{
	Material()
	{
		albedo = Color(1, 1, 1);
	}

	Color albedo;	//!< ”½ŽË—¦
};

#endif // !_MATERIAL_H_

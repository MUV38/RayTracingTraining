#include "my_shade_rec.h"

namespace My{
	ShadeRec::ShadeRec() 
	: is_intesect(false)
	, color(1, 1, 1)
	, normal(0, 0, 1)
	, hit_point(0, 0, 0)
	{
	}

	ShadeRec::~ShadeRec(){
	}
}
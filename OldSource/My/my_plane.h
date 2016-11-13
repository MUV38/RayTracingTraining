#ifndef MY_PLANE_H
#define	MY_PLANE_H

#include "../vec.h"
#include "my_object.h"

namespace My{
	/**
	* @brief ñ≥å¿ïΩñ ÇÃíËã`
	*/
	class Plane : public Object
	{
	public:
		Plane()
		: normal(0, 1, 0){}
		~Plane(){}
	public:
		bool Hit(ShadeRec* sr, double* tmin, double t_max, edupt::Vec* normal, const Ray& ray) override;
	public:
		edupt::Vec pos;		// à íu
		edupt::Vec normal;	// ñ@ê¸
	};
}

#endif // !MY_PLANE_H

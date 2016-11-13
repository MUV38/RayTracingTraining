#ifndef MY_PLANE_H
#define	MY_PLANE_H

#include "../vec.h"
#include "my_object.h"

namespace My{
	/**
	* @brief 無限平面の定義
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
		edupt::Vec pos;		// 位置
		edupt::Vec normal;	// 法線
	};
}

#endif // !MY_PLANE_H

/**
* @file		my_sphere.h
* @brief	球の定義
* @author	Toru Miyawaki
*/

#ifndef MY_SPHERE_H
#define MY_SPHERE_H

#include "../vec.h"
#include "my_object.h"

namespace My{
	/**
	* @brief 球の定義
	*/
	class Sphere : public Object{
	public:
		Sphere() 
		: radius(1) 
		, pos(0, 0, 0)
		{}
		~Sphere(){}
	public:
		bool Hit(ShadeRec* sr, double* tmin, double t_max, edupt::Vec* normal, const Ray& ray) override;
	public:
		float		radius;	// 半径
		edupt::Vec	pos;	// 中心点
	};
};

#endif // !MY_SPHERE_H

/**
* @file		my_sphere.h
* @brief	���̒�`
* @author	Toru Miyawaki
*/

#ifndef MY_SPHERE_H
#define MY_SPHERE_H

#include "../vec.h"
#include "my_object.h"

namespace My{
	/**
	* @brief ���̒�`
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
		float		radius;	// ���a
		edupt::Vec	pos;	// ���S�_
	};
};

#endif // !MY_SPHERE_H

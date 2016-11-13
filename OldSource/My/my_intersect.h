/**
* @file		my_intersect.h
* @brief	�Փ˔���̒�`
* @author	Toru Miyawaki
*/

#ifndef MY_INTERSECT_H
#define MY_INTERSECT_H

#include "my_ray.h"
#include "my_sphere.h"

namespace My{
	/**
	* @brief ���ƃ��C�̏Փ˔���
	* @param [in] ray		���C
	* @param [in] sphere	��
	* @return �Փ˂�����
	*/
	bool IntersectSphere(const Ray& ray, const Sphere& sphere);
};

#endif // !MY_INTERSECT_H

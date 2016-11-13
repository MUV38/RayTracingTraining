/**
* @file my_ray.h
* @brief ���C�̒�`
* @author Toru Miyawaki
*/

#ifndef MY_RAY_H
#define MY_RAY_H

#include "../vec.h"

namespace My{
	/**
	* @brief ���C�̒�`
	*/
	struct Ray{
		edupt::Vec	origin;
		edupt::Vec	direction;
	};
};

#endif // !MY_RAY_H

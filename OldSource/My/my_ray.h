/**
* @file my_ray.h
* @brief レイの定義
* @author Toru Miyawaki
*/

#ifndef MY_RAY_H
#define MY_RAY_H

#include "../vec.h"

namespace My{
	/**
	* @brief レイの定義
	*/
	struct Ray{
		edupt::Vec	origin;
		edupt::Vec	direction;
	};
};

#endif // !MY_RAY_H

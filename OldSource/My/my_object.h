#ifndef MY_OBJECT_H
#define	MY_OBJECT_H

#include "../vec.h"
#include "my_ray.h"
#include "my_shade_rec.h"

namespace My{
	/**
	* @brief オブジェクト基底クラス
	*/
	class Object{
	public:
		Object();
		virtual ~Object();

	public:
		/**
		* @brief レイとの交差判定
		* @param [out]	sr		シェーディング情報
		* @param [out]	tmin	レイと交点の距離
		* @param [out]	normal	法線
		* @param [in]	ray		レイ
		*/
		virtual bool Hit(ShadeRec* sr, double* tmin, double t_max, edupt::Vec* normal, const Ray& ray) = 0;

	public:
		edupt::Vec	color;	// 色
	};

}

#endif // !MY_OBJECT_H

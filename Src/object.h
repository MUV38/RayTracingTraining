#ifndef _OBJECT_H
#define _OBJECT_H

#include "vec.h"
#include "ray.h"
#include "shade_record.h"

/**
* @brief オブジェクトクラス
* 
* シーンに存在するすべてのオブジェクトはこれを継承する
*/
class Object
{
public:
	Object(){}
	virtual ~Object(){}

public:
	/**
	* @brief レイとの交差判定
	* @param [out]	sr		シェーディング情報
	* @param [out]	tmin	レイと交点の距離
	* @param [out]	normal	法線
	* @param [in]	ray		レイ
	*/
	virtual bool Hit(ShadeRecord* sr, double* tmin, double t_max, Vec* normal, const Ray& ray) = 0;

public:
	Material m_material;
};


#endif // !_OBJECT_H

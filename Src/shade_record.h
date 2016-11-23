#ifndef _SHADE_RECORD_H_
#define	_SHADE_RECORD_H_

#include "material.h"

/**
* @beief シェーディング情報を詰めた構造体
*/
struct ShadeRecord
{
	ShadeRecord()
	{
		is_intersect = false;
	}

	bool		is_intersect;	//!< レイと交差したか
	Material*	material;		//!< マテリアル
	Vec			normal;			//!< 法線
	Vec			hit_point;		//!< 交差点
};

#endif // !_SHADE_RECORD_H_

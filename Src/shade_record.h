#ifndef _SHADE_RECORD_H_
#define	_SHADE_RECORD_H_

#include "material.h"

/**
* @beief �V�F�[�f�B���O�����l�߂��\����
*/
struct ShadeRecord
{
	ShadeRecord()
	{
		is_intersect = false;
	}

	bool		is_intersect;	//!< ���C�ƌ���������
	Material*	material;		//!< �}�e���A��
	Vec			normal;			//!< �@��
	Vec			hit_point;		//!< �����_
};

#endif // !_SHADE_RECORD_H_

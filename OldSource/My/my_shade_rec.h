#ifndef MY_SHADE_REC_H
#define	MY_SHADE_REC_H

#include "../material.h"

namespace My{
	/**
	* @brief �V�F�[�f�B���O�����l�߂��N���X
	*/
	class ShadeRec
	{
	public:
		ShadeRec();
		~ShadeRec();

	public:
		bool			is_intesect;
		edupt::Color	color;
		edupt::Vec		normal;
		edupt::Vec		hit_point;
	};

}

#endif // !MY_SHADE_REC_H

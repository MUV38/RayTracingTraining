#ifndef MY_OBJECT_H
#define	MY_OBJECT_H

#include "../vec.h"
#include "my_ray.h"
#include "my_shade_rec.h"

namespace My{
	/**
	* @brief �I�u�W�F�N�g���N���X
	*/
	class Object{
	public:
		Object();
		virtual ~Object();

	public:
		/**
		* @brief ���C�Ƃ̌�������
		* @param [out]	sr		�V�F�[�f�B���O���
		* @param [out]	tmin	���C�ƌ�_�̋���
		* @param [out]	normal	�@��
		* @param [in]	ray		���C
		*/
		virtual bool Hit(ShadeRec* sr, double* tmin, double t_max, edupt::Vec* normal, const Ray& ray) = 0;

	public:
		edupt::Vec	color;	// �F
	};

}

#endif // !MY_OBJECT_H

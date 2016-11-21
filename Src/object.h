#ifndef _OBJECT_H
#define _OBJECT_H

#include "vec.h"
#include "ray.h"
#include "shade_record.h"

/**
* @brief �I�u�W�F�N�g�N���X
* 
* �V�[���ɑ��݂��邷�ׂẴI�u�W�F�N�g�͂�����p������
*/
class Object
{
public:
	Object(){}
	virtual ~Object(){}

public:
	/**
	* @brief ���C�Ƃ̌�������
	* @param [out]	sr		�V�F�[�f�B���O���
	* @param [out]	tmin	���C�ƌ�_�̋���
	* @param [out]	normal	�@��
	* @param [in]	ray		���C
	*/
	virtual bool Hit(ShadeRecord* sr, double* tmin, double t_max, Vec* normal, const Ray& ray) = 0;

public:
	Material m_material;
};


#endif // !_OBJECT_H

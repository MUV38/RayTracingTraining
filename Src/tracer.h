#ifndef _TRACER_H_
#define	_TRACER_H_

#include "world.h"

/**
* @brief ���C�g���[�T�[�̒�`
*/
class Tracer
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param [in] world ���[���h��`�N���X
	*/
	Tracer(World* world)
		: m_world(world)
	{}

	~Tracer(){}

private:
	Tracer() {}
	Tracer(const Tracer& obj){}

public:
	/**
	* @brief ���C�̒ǐ�
	* @param [in] ray ���C
	* @return �`��F
	*/
	virtual Color TraceRay(const Ray& ray, double t_max) = 0;

protected:
	World* m_world;
};

#endif // !_TRACER_H_

#ifndef MY_TRACER_H
#define	MY_TRACER_H

#include "../material.h"
#include "my_world.h"
#include "my_ray.h"

namespace My{
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
		Tracer(World* world);
		~Tracer();
	private:
		Tracer(){}

	public:
		/**
		* @brief ���C�̒ǐ�
		* @param [in] ray ���C
		* @return �`��F
		*/
		virtual edupt::Color TraceRay(const Ray& ray, double t_max) = 0;

	protected:
		World* m_world;
	};

}

#endif // !MY_TRACER_H

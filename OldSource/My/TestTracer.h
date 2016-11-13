#ifndef TEST_TRACER_H
#define	TEST_TRACER_H

#include "my_tracer.h"

namespace My{
	/**
	* @brief �e�X�g�p�g���[�T�[
	*/
	class TestTracer : public Tracer
	{
	public:
		TestTracer(World* world);
		~TestTracer();


	public:
		// ���C�̒ǐ�
		edupt::Color TraceRay(const Ray& ray, double t_max);

	private:
		int m_bounsNum;
	};

}

#endif // !TEST_TRACER_H

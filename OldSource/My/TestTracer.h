#ifndef TEST_TRACER_H
#define	TEST_TRACER_H

#include "my_tracer.h"

namespace My{
	/**
	* @brief テスト用トレーサー
	*/
	class TestTracer : public Tracer
	{
	public:
		TestTracer(World* world);
		~TestTracer();


	public:
		// レイの追跡
		edupt::Color TraceRay(const Ray& ray, double t_max);

	private:
		int m_bounsNum;
	};

}

#endif // !TEST_TRACER_H

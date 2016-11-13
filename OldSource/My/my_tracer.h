#ifndef MY_TRACER_H
#define	MY_TRACER_H

#include "../material.h"
#include "my_world.h"
#include "my_ray.h"

namespace My{
	/**
	* @brief レイトレーサーの定義
	*/
	class Tracer
	{
	public:
		/**
		* @brief コンストラクタ
		* @param [in] world ワールド定義クラス
		*/
		Tracer(World* world);
		~Tracer();
	private:
		Tracer(){}

	public:
		/**
		* @brief レイの追跡
		* @param [in] ray レイ
		* @return 描画色
		*/
		virtual edupt::Color TraceRay(const Ray& ray, double t_max) = 0;

	protected:
		World* m_world;
	};

}

#endif // !MY_TRACER_H

#ifndef _TRACER_H_
#define	_TRACER_H_

#include "world.h"

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
	Tracer(World* world)
		: m_world(world)
	{}

	~Tracer(){}

private:
	Tracer() {}
	Tracer(const Tracer& obj){}

public:
	/**
	* @brief レイの追跡
	* @param [in] ray レイ
	* @return 描画色
	*/
	virtual Color TraceRay(const Ray& ray, double t_max) = 0;

protected:
	World* m_world;
};

#endif // !_TRACER_H_

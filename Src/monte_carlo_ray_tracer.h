#ifndef _MONTE_CARLO_RAY_TRACER_H_
#define	_MONTE_CARLO_RAY_TRACER_H_

#include "tracer.h"
#include "random.h"

#include "../Extension/vdb/vdb.h"

class MonteCarloRayTracer : public Tracer
{
public:
	MonteCarloRayTracer(World* world) : Tracer(world){}
	~MonteCarloRayTracer(){}

public:
	/**
	* @brief レイの追跡
	* @param [in] ray レイ
	* @return 描画色
	*/
	Color TraceRay(const Ray& ray, Random& random, const int depth) override
	{
		// 背景色
		Color backgroundColor;
		{
			Vec unit_direction = normalize(ray.direction);
			double t = 0.5 * (unit_direction.y + 1.0);
			backgroundColor = (1.0 - t) * Vec(1.0, 1.0, 1.0) + t * Vec(0.5, 0.7, 1.0);

			backgroundColor = Color(0, 0, 0);
		}

		// 打ち切りチェック
		const int MAX_DEPTH = 10;
		if(depth >= MAX_DEPTH){ return Color(); }

		// オブジェクトとの交差判定
		ShadeRecord sr;
		m_world->HitObjects(ray, &sr);

		// レイが交差しているか
		if(!sr.is_intersect){ return backgroundColor; }

		// マテリアル取得
		const Material *now_material = sr.material;

		// 光源にヒットしたら放射項だけ返して終わる。
		// （今回、光源は反射率0と仮定しているため）
		const Color emission = now_material->GetEmission();
		if (emission.x > 0.0 || emission.y > 0.0 || emission.z > 0.0) {
			return emission;
		}

		// デバッグ
		vdb_point(sr.hit_point.x, sr.hit_point.y, sr.hit_point.z);

		// 次の方向をサンプリング + その方向のBRDF項の値を得る。
		double pdf = -1;
		Color brdf_value;
		const Vec dir_out = now_material->Sample(random, ray.direction, sr.normal, &pdf, &brdf_value);

		// cos項。
		const double cost = dot(sr.normal, dir_out);

		// レンダリング方程式をモンテカルロ積分によって再帰的に解く。
		const Color L = multiply(
			brdf_value,
			TraceRay(Ray(sr.hit_point, dir_out), random, depth + 1))
			* cost / pdf;
		return L;
	}

private:

};


#endif // !_MONTE_CARLO_RAY_TRACER_H_

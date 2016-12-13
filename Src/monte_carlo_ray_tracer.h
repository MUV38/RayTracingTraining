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
	* @brief ���C�̒ǐ�
	* @param [in] ray ���C
	* @return �`��F
	*/
	Color TraceRay(const Ray& ray, Random& random, const int depth) override
	{
		// �w�i�F
		Color backgroundColor;
		{
			Vec unit_direction = normalize(ray.direction);
			double t = 0.5 * (unit_direction.y + 1.0);
			backgroundColor = (1.0 - t) * Vec(1.0, 1.0, 1.0) + t * Vec(0.5, 0.7, 1.0);

			backgroundColor = Color(0, 0, 0);
		}

		// �ł��؂�`�F�b�N
		const int MAX_DEPTH = 10;
		if(depth >= MAX_DEPTH){ return Color(); }

		// �I�u�W�F�N�g�Ƃ̌�������
		ShadeRecord sr;
		m_world->HitObjects(ray, &sr);

		// ���C���������Ă��邩
		if(!sr.is_intersect){ return backgroundColor; }

		// �}�e���A���擾
		const Material *now_material = sr.material;

		// �����Ƀq�b�g��������ˍ������Ԃ��ďI���B
		// �i����A�����͔��˗�0�Ɖ��肵�Ă��邽�߁j
		const Color emission = now_material->GetEmission();
		if (emission.x > 0.0 || emission.y > 0.0 || emission.z > 0.0) {
			return emission;
		}

		// �f�o�b�O
		vdb_point(sr.hit_point.x, sr.hit_point.y, sr.hit_point.z);

		// ���̕������T���v�����O + ���̕�����BRDF���̒l�𓾂�B
		double pdf = -1;
		Color brdf_value;
		const Vec dir_out = now_material->Sample(random, ray.direction, sr.normal, &pdf, &brdf_value);

		// cos���B
		const double cost = dot(sr.normal, dir_out);

		// �����_�����O�������������e�J�����ϕ��ɂ���čċA�I�ɉ����B
		const Color L = multiply(
			brdf_value,
			TraceRay(Ray(sr.hit_point, dir_out), random, depth + 1))
			* cost / pdf;
		return L;
	}

private:

};


#endif // !_MONTE_CARLO_RAY_TRACER_H_

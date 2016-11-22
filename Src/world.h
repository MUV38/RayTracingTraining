#ifndef _WORLD_H_
#define	_WORLD_H_

#include <vector>
#include "object.h"

/**
* @brief ���E��`�N���X
*/
class World {
public:
	World(){}
	~World()
	{
		for (auto it = m_object.begin(); it != m_object.end(); it++) {
			delete *it;
			*it = nullptr;
		}
		m_object.clear();
	}

	/**
	* @brief �I�u�W�F�N�g�ǉ�
	* @pram [in] object �I�u�W�F�N�g
	*/
	void AddObject(Object* object)
	{
		m_object.push_back(object);
	}

	/**
	* @brief �S�I�u�W�F�N�g�ƃ��C�Ƃ̌�������
	*/
	bool HitObjects(const Ray& ray, ShadeRecord* rec)
	{
		ShadeRecord sr;
		double t = 0;
		double tmin = FLT_MAX;
		Vec normal = Vec(0, 1, 0);

		for (auto& obj : m_object) {
			// ���C�ƈ�ԋ߂��_���̗p����
			if (obj->Hit(&sr, &t, &normal, ray) && t < tmin) {
				sr.is_intersect = true;
				sr.normal = normal;
				memcpy(&sr.material, &obj->material, sizeof(Material));
				tmin = t;
			}
		}

		*rec = sr;

		return sr.is_intersect;
	}

public:
	void SetBackgroundColor(const Color& color) { m_background_color = color; }
	Color GetBackgroundColor() const { return m_background_color; }

private:
	std::vector<Object*>	m_object;
	Color					m_background_color;
};

#endif // !_WORLD_H_

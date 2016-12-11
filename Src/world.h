#ifndef _WORLD_H_
#define	_WORLD_H_

#include <vector>
#include "object.h"

/**
* @brief 世界定義クラス
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
	* @brief オブジェクト追加
	* @pram [in] object オブジェクト
	*/
	void AddObject(Object* object)
	{
		m_object.push_back(object);
	}

	/**
	* @brief 全オブジェクトとレイとの交差判定
	*/
	bool HitObjects(const Ray& ray, ShadeRecord* rec)
	{
		double t = FLT_MAX;
		double tmin = FLT_MAX;
		Vec normal = Vec(0, 1, 0);

		for (auto& obj : m_object) {
			// レイと一番近い点を採用する
			t = FLT_MAX;
			if (obj->Hit(rec, &t, &normal, ray)) {
				if(t < tmin){
					rec->is_intersect = true;
					rec->normal = normal;
					rec->material = obj->material;
					tmin = t;
				}
			}
		}

		return rec->is_intersect;
	}

public:
	void SetBackgroundColor(const Color& color) { m_background_color = color; }
	Color GetBackgroundColor() const { return m_background_color; }

private:
	std::vector<Object*>	m_object;
	Color					m_background_color;
};

#endif // !_WORLD_H_

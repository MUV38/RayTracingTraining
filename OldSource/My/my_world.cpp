#include "my_world.h"

namespace My{
	World::World(){
	}

	World::~World(){
		for(auto it=m_object.begin() ; it != m_object.end() ; it++){
			delete *it;
			*it = nullptr;
		}
		m_object.clear();
	}

	// オブジェクト追加
	void World::AddObject(Object* object){
		m_object.push_back(object);
	}

	// 全オブジェクトとレイとの交差判定
	bool World::HitObjects(const Ray& ray, double t_max, ShadeRec* rec){
		ShadeRec sr;
		double t = 0;
		double tmin= t_max;
		edupt::Vec normal = edupt::Vec(0, 1, 0);

		for(auto& obj : m_object){
			// レイと一番近い点を採用する
			if(obj->Hit(&sr, &t, tmin, &normal, ray) && t < tmin){
				sr.is_intesect = true;
				sr.normal = normal;
				sr.color = obj->color;
				tmin = t;
			}
		}

		*rec = sr;

		return sr.is_intesect;
	}
}
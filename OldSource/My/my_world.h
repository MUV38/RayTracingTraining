#ifndef MY_WORLD_H
#define	MY_WORLD_H

#include <vector>
#include "my_object.h"
#include "my_shade_rec.h"

namespace My{
	/**
	* @brief 世界定義クラス
	*/
	class World{
	public:
		World();
		~World();

		/**
		* @brief オブジェクト追加
		* @pram [in] object オブジェクト
		*/
		void AddObject(Object* object);

		/**
		* @brief 全オブジェクトとレイとの交差判定
		*/
		bool HitObjects(const Ray& ray, double t_max, ShadeRec* rec);

	public:
		void SetBackgroundColor(const edupt::Color& color){ m_background_color = color; }
		edupt::Color GetBackgroundColor() const { return m_background_color; }

	private:
		std::vector<Object*>	m_object;
		edupt::Color			m_background_color;
	};

}

#endif // !MY_WORLD_H

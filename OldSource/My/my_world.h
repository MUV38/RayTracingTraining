#ifndef MY_WORLD_H
#define	MY_WORLD_H

#include <vector>
#include "my_object.h"
#include "my_shade_rec.h"

namespace My{
	/**
	* @brief ���E��`�N���X
	*/
	class World{
	public:
		World();
		~World();

		/**
		* @brief �I�u�W�F�N�g�ǉ�
		* @pram [in] object �I�u�W�F�N�g
		*/
		void AddObject(Object* object);

		/**
		* @brief �S�I�u�W�F�N�g�ƃ��C�Ƃ̌�������
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

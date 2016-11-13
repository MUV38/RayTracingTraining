#ifndef MY_PLANE_H
#define	MY_PLANE_H

#include "../vec.h"
#include "my_object.h"

namespace My{
	/**
	* @brief �������ʂ̒�`
	*/
	class Plane : public Object
	{
	public:
		Plane()
		: normal(0, 1, 0){}
		~Plane(){}
	public:
		bool Hit(ShadeRec* sr, double* tmin, double t_max, edupt::Vec* normal, const Ray& ray) override;
	public:
		edupt::Vec pos;		// �ʒu
		edupt::Vec normal;	// �@��
	};
}

#endif // !MY_PLANE_H

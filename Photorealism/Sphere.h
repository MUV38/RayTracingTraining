#ifndef SPHERE_H_
#define SPHERE_H_

#include <cmath>
#include "Vec3.h"
#include "Ray.h"
#include "Hit.h"

class Sphere
{
public:
    Vec3    center;
    double  radius;

    Sphere(const Vec3& center, double radius)
        : center(center)
        , radius(radius)
    {}

    /// �Փ˔���
    bool Intersect(const Ray& ray, Hit& res) const
    {
        // 2���������̌W��
        double b = Dot(ray.direction, ray.origin - center);
        double c = (ray.origin - center).length2() - radius * radius;
        // ���ʎ�
        double D = b * b - c;
        // ���̌�⋗��
        double t1 = -b - std::sqrt(D);
        double t2 = -b + std::sqrt(D);

        if (t1 > 10000 || t2 < 0) { return false; }

        double t = t1;
        if (t < 0)
        {
            t = t2;
            if (t2 > 10000) { return false; }
        }

        // �Փˏ����i�[
        res.t = t;
        res.hitPos = ray(t);
        res.hitNormal = Normalize(res.hitPos - center);
        res.hitSphere = this;

        return true;
    }
};

#endif // !SPHERE_H_

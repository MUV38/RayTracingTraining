#ifndef SKY_H_
#define SKY_H_

#include "Vec3.h"
#include "Ray.h"

/// ��N���X
class Sky
{
public:
    /// ���ˋP�x�擾
    virtual Vec3 GetRadiance(const Ray& ray) const = 0;
};

/// �P�F��N���X
class UniformSky : public Sky
{
public:
    Vec3 color;

    UniformSky(const Vec3& color) : color(color) {}
    
    Vec3 GetRadiance(const Ray& ray) const override
    {
        return color;
    }
};

/// �V���v���ȋ�N���X
class SimpleSky : public Sky
{
public:
    SimpleSky() {}

    Vec3 GetRadiance(const Ray& ray) const override
    {
        double t = (ray.direction.y + 1.0) / 2.0;
        return (1.0 - t) * Vec3(1.0) + t * Vec3(0.7, 0.8, 1.0);
    }
};

#endif // !SKY_H_

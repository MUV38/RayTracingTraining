#ifndef RAY_H_
#define RAY_H_

#include <iostream>
#include "Vec3.h"

class Ray
{
public:
    Vec3 origin;
    Vec3 direction;
    double tmin = 0.001;

    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}

    Vec3 operator()(double t) const { return origin + t * direction; }
};

std::ostream& operator<<(std::ostream& stream, const Ray& ray)
{
    stream << "origin: " << ray.origin << "direction: " << ray.direction;
    return stream;
}

#endif // !RAY_H_

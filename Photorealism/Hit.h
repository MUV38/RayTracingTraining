#ifndef HIT_H_
#define HIT_H_

#include "Vec3.h"

class Sphere;

class Hit
{
public:
    double          t;
    Vec3            hitPos;
    Vec3            hitNormal;
    const Sphere*   hitSphere;

    Hit() : t(10000) {}
};

#endif // !HIT_H_

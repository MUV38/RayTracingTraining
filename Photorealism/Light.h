#ifndef LIGHT_H_
#define LIGHT_H_

#include "Vec3.h"

class Light
{
public:
    Vec3 color;

    Light(const Vec3& color) : color(color) {}

    /// ƒŒƒ“ƒ_ƒŠƒ“ƒO•û’öŽ®‚ÌLe
    Vec3 Le()
    {
        return color;
    }
};

#endif // !LIGHT_H_

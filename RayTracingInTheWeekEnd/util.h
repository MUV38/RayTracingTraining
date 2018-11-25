#ifndef UTIL_H_
#define UTIL_H_

#include "vec3.h"

static long long g_rnd_seed = 0;

inline void srand48(long long s) {
    g_rnd_seed = s;
    g_rnd_seed = (g_rnd_seed << 16) + 0x330E;
}
inline double drand48()
{
    g_rnd_seed = g_rnd_seed * 0x5DEECE66D + 0xB;
    return (g_rnd_seed & 0xFFFFFFFFFFFF)*(1.0 / 281474976710656.0);
}

inline vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}

inline void get_sphere_uv(const vec3& p, float& u, float& v)
{
    float phi = atan2(p.z(), p.x());
    float theta = asin(p.y());
    u = 1 - (phi + M_PI) / (2 * M_PI);
    v = (theta + M_PI / 2) / M_PI;
}

#endif // !UTIL_H_

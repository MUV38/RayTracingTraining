#ifndef SPHERE_H_
#define SPHERE_H_

#include "MathUtil.h"
#include <memory>
#include "Vec3.h"
#include "Ray.h"
#include "Hit.h"
#include "Material.h"
#include "Light.h"

class Sphere
{
public:
    Vec3    center;
    double  radius;
    std::shared_ptr<Material> material;
    std::shared_ptr<Light> light;

    Sphere(const Vec3& center, double radius, const std::shared_ptr<Material>& material, const std::shared_ptr<Light>& light)
        : center(center)
        , radius(radius)
        , material(material)
        , light(light)
    {}

    /// Õ“Ë”»’è
    bool Intersect(const Ray& ray, Hit& res) const
    {
        // 2Ÿ•û’ö®‚ÌŒW”
        double b = Dot(ray.direction, ray.origin - center);
        double c = (ray.origin - center).length2() - radius * radius;
        // ”»•Ê®
        double D = b * b - c;
        // ‰ğ‚ÌŒó•â‹——£
        double t1 = -b - std::sqrt(D);
        double t2 = -b + std::sqrt(D);

        if (t1 > 10000 || t2 < 0) { return false; }

        double t = t1;
        if (t < 0)
        {
            t = t2;
            if (t2 > 10000) { return false; }
        }

        // Õ“Ëî•ñ‚ğŠi”[
        res.t = t;
        res.hitPos = ray(t);
        res.hitNormal = Normalize(res.hitPos - center);
        res.hitSphere = this;

        return true;
    }
};

#endif // !SPHERE_H_

#ifndef AGGREGATE_H_
#define AGGREGATE_H_

#include <memory>
#include <vector>
#include "Ray.h"
#include "Hit.h"
#include "Sphere.h"

class Aggregate
{
public:
    std::vector<std::shared_ptr<Sphere>> spheres;

    Aggregate() {}
    Aggregate(const std::vector<std::shared_ptr<Sphere>>& spheres)
        : spheres(spheres)
    {}

    /// •¨‘Ì‚Ì’Ç‰Á
    void Add(const std::shared_ptr<Sphere>& s)
    {
        spheres.push_back(s);
    }

    /// ƒŒƒC‚Æ‚ÌÕ“Ë”»’è
    bool Intersect(const Ray& ray, Hit& res) const
    {
        bool hit = false;
        for (auto&& s : spheres)
        {
            Hit resTmp;
            if (s->Intersect(ray, resTmp))
            {
                if (resTmp.t < res.t)
                {
                    hit = true;
                    res = resTmp;
                }
            }
        }
        return hit;
    }
};

#endif // !AGGREGATE_H_

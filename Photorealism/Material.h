#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "MathUtil.h"
#include "Vec3.h"
#include "Random.h"

/// 反射ベクトル
Vec3 Reflect(const Vec3& v, const Vec3& n)
{
    return -v + 2.0 * Dot(v, n) * n;
}

/// ローカル座標系のベクトルからcosThetaを計算
double CosTheta(const Vec3& v)
{
    return v.y;
}

class Material
{
public:
    /// サンプル
    virtual Vec3 Sample(const Vec3& wo, Vec3& wi, double& pdf) const = 0;
};

class Diffuse : public Material
{
public:
    Vec3 rho; ///< 反射率

    Diffuse(const Vec3& rho) : rho(rho) {}

    /// サンプル
    Vec3 Sample(const Vec3& wo, Vec3& wi, double& pdf) const override
    {
        // 一様散乱
        double u = Rnd();
        double v = Rnd();

        // theta, phi
        double theta = 0.5 * std::acos(1.0 - 2.0 * u);
        double phi = 2.0 * M_PI * v;

        // x, y, z
        double x = std::cos(phi) * std::sin(theta);
        double y = std::cos(theta);
        double z = std::sin(phi) * std::sin(theta);

        // サンプリング方向
        wi = Vec3(x, y, z);

        // 確率密度関数の値
        pdf = std::cos(theta) / M_PI;

        return rho / M_PI;
    }
};

class Mirror : public Material
{
public:
    Mirror() {}

    Vec3 Sample(const Vec3& wo, Vec3& wi, double& pdf) const override
    {
        // サンプリング方向
        wi = Reflect(wo, Vec3(0, 1, 0));

        // 確率密度関数の値
        pdf = 1.0;

        return 1.0 / CosTheta(wi) * Vec3(1);
    }
};

#endif // !MATERIAL_H_

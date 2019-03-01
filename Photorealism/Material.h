#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "MathUtil.h"
#include "Vec3.h"
#include "Random.h"

/// ローカル座標系のベクトルからcosThetaを計算
double CosTheta(const Vec3& v)
{
    return v.y;
}

/// ローカル座標系のベクトルからcosThetaを計算(絶対値)
double AbsCosTheta(const Vec3& v)
{
    return std::abs(v.y);
}

/// 反射ベクトル
Vec3 Reflect(const Vec3& v, const Vec3& n)
{
    return -v + 2.0 * Dot(v, n) * n;
}

/// フレネル反射率
double fresnel(const Vec3& v, const Vec3& n, double n1, double n2)
{
    double f0 = std::pow((n1 - n2) / (n1 + n2), 2.0);
    double cos = AbsCosTheta(v);
    return f0 + (1.0 - f0) * std::pow(1.0 - cos, 5.0);
}

/// 屈折ベクトル
bool Refract(const Vec3& v, Vec3& r, const Vec3& n, double n1, double n2)
{
    double cos = AbsCosTheta(v);
    double sin = std::sqrt(std::max(1.0 - cos * cos, 0.0));
    double alpha = n1 / n2 * sin;

    // 全反射
    if (alpha * alpha > 1.0) { return false; }

    // 屈折
    r = n1 / n2 * (-v + Dot(v, n) * n) - std::sqrt(1.0 - alpha * alpha) * n;

    return true;
}

/// マテリアル
class Material
{
public:
    /// サンプル
    virtual Vec3 Sample(const Vec3& wo, Vec3& wi, double& pdf) const = 0;
};

/// ディフューズ
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

/// ミラー
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

/// ガラス
class Glass : public Material
{
public:
    double ior; // 屈折率

    Glass(double ior) : ior(ior) {}

    Vec3 Sample(const Vec3& wo, Vec3& wi, double& pdf) const override
    {
        // カラスに入射しているか
        bool isEntering = CosTheta(wo) > 0.0;

        // 入射と出射で屈折率、法線を入れ替え
        double n1;  // 入射側屈折率
        double n2;  // 出射側屈折率
        Vec3 normal;
        if (isEntering)
        {
            n1 = 1.0;
            n2 = ior;
            normal = Vec3(0, 1, 0);
        }
        else
        {
            n1 = ior;
            n2 = 0.0;
            normal = Vec3(0, -1, 0);
        }

        // フレネル反射率
        double fr = fresnel(wo, normal, n1, n2);

        // 反射
        if (Rnd() < fr)
        {
            wi = Reflect(wo, normal);
            pdf = fr;
            return fr / AbsCosTheta(wi) * Vec3(1);
        }
        else // 屈折
        {
            if (Refract(wo, wi, normal, n1, n2))
            {
                pdf = 1.0 - fr;
                return std::pow(n1/ n2, 2.0) * (1.0 - fr) / AbsCosTheta(wi) * Vec3(1);
            }
            else // 全反射
            {
                wi = Reflect(wo, normal);
                pdf = 1.0 - fr;
                return (1.0 - fr) / AbsCosTheta(wi) * Vec3(1);
            }
        }
    }
};

#endif // !MATERIAL_H_

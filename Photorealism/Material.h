#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "MathUtil.h"
#include "Vec3.h"
#include "Random.h"

/// ���˃x�N�g��
Vec3 Reflect(const Vec3& v, const Vec3& n)
{
    return -v + 2.0 * Dot(v, n) * n;
}

/// ���[�J�����W�n�̃x�N�g������cosTheta���v�Z
double CosTheta(const Vec3& v)
{
    return v.y;
}

class Material
{
public:
    /// �T���v��
    virtual Vec3 Sample(const Vec3& wo, Vec3& wi, double& pdf) const = 0;
};

class Diffuse : public Material
{
public:
    Vec3 rho; ///< ���˗�

    Diffuse(const Vec3& rho) : rho(rho) {}

    /// �T���v��
    Vec3 Sample(const Vec3& wo, Vec3& wi, double& pdf) const override
    {
        // ��l�U��
        double u = Rnd();
        double v = Rnd();

        // theta, phi
        double theta = 0.5 * std::acos(1.0 - 2.0 * u);
        double phi = 2.0 * M_PI * v;

        // x, y, z
        double x = std::cos(phi) * std::sin(theta);
        double y = std::cos(theta);
        double z = std::sin(phi) * std::sin(theta);

        // �T���v�����O����
        wi = Vec3(x, y, z);

        // �m�����x�֐��̒l
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
        // �T���v�����O����
        wi = Reflect(wo, Vec3(0, 1, 0));

        // �m�����x�֐��̒l
        pdf = 1.0;

        return 1.0 / CosTheta(wi) * Vec3(1);
    }
};

#endif // !MATERIAL_H_

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "MathUtil.h"
#include "Vec3.h"
#include "Random.h"

/// ���[�J�����W�n�̃x�N�g������cosTheta���v�Z
double CosTheta(const Vec3& v)
{
    return v.y;
}

/// ���[�J�����W�n�̃x�N�g������cosTheta���v�Z(��Βl)
double AbsCosTheta(const Vec3& v)
{
    return std::abs(v.y);
}

/// ���˃x�N�g��
Vec3 Reflect(const Vec3& v, const Vec3& n)
{
    return -v + 2.0 * Dot(v, n) * n;
}

/// �t���l�����˗�
double fresnel(const Vec3& v, const Vec3& n, double n1, double n2)
{
    double f0 = std::pow((n1 - n2) / (n1 + n2), 2.0);
    double cos = AbsCosTheta(v);
    return f0 + (1.0 - f0) * std::pow(1.0 - cos, 5.0);
}

/// ���܃x�N�g��
bool Refract(const Vec3& v, Vec3& r, const Vec3& n, double n1, double n2)
{
    double cos = AbsCosTheta(v);
    double sin = std::sqrt(std::max(1.0 - cos * cos, 0.0));
    double alpha = n1 / n2 * sin;

    // �S����
    if (alpha * alpha > 1.0) { return false; }

    // ����
    r = n1 / n2 * (-v + Dot(v, n) * n) - std::sqrt(1.0 - alpha * alpha) * n;

    return true;
}

/// �}�e���A��
class Material
{
public:
    /// �T���v��
    virtual Vec3 Sample(const Vec3& wo, Vec3& wi, double& pdf) const = 0;
};

/// �f�B�t���[�Y
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

/// �~���[
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

/// �K���X
class Glass : public Material
{
public:
    double ior; // ���ܗ�

    Glass(double ior) : ior(ior) {}

    Vec3 Sample(const Vec3& wo, Vec3& wi, double& pdf) const override
    {
        // �J���X�ɓ��˂��Ă��邩
        bool isEntering = CosTheta(wo) > 0.0;

        // ���˂Əo�˂ŋ��ܗ��A�@�������ւ�
        double n1;  // ���ˑ����ܗ�
        double n2;  // �o�ˑ����ܗ�
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

        // �t���l�����˗�
        double fr = fresnel(wo, normal, n1, n2);

        // ����
        if (Rnd() < fr)
        {
            wi = Reflect(wo, normal);
            pdf = fr;
            return fr / AbsCosTheta(wi) * Vec3(1);
        }
        else // ����
        {
            if (Refract(wo, wi, normal, n1, n2))
            {
                pdf = 1.0 - fr;
                return std::pow(n1/ n2, 2.0) * (1.0 - fr) / AbsCosTheta(wi) * Vec3(1);
            }
            else // �S����
            {
                wi = Reflect(wo, normal);
                pdf = 1.0 - fr;
                return (1.0 - fr) / AbsCosTheta(wi) * Vec3(1);
            }
        }
    }
};

#endif // !MATERIAL_H_

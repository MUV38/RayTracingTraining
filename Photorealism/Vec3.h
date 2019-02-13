#ifndef VEC3_H_
#define VEC3_H_

#include "MathUtil.h"
#include <iostream>

/// �R�����x�N�g���N���X
class Vec3
{
public:
    double x, y, z;

    Vec3() { x = y = z = 0; }
    Vec3(double x) : x(x), y(x), z(x) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    /// �x�N�g���̒���
    inline double length() const { return std::sqrt(length2()); }
    inline double length2() const { return x * x + y * y + z * z; }

    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }
    Vec3& operator+=(const Vec3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;

        return *this;
    }
    Vec3& operator-=(const Vec3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }
    Vec3& operator*=(const Vec3& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;

        return *this;
    }
    Vec3& operator/=(const Vec3& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;

        return *this;
    }
};

/// �x�N�g�����m�̉��Z
Vec3 operator+(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
Vec3 operator-(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
Vec3 operator*(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
Vec3 operator/(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

/// �x�N�g���ƃX�J���[�̉��Z
Vec3 operator+(const Vec3& v, const double k)
{
    return Vec3(v.x + k, v.y + k, v.z + k);
}
Vec3 operator+(const double k, const Vec3& v)
{
    return v + k;
}
Vec3 operator-(const Vec3& v, const double k)
{
    return Vec3(v.x - k, v.y - k, v.z - k);
}
Vec3 operator-(const double k, const Vec3& v)
{
    return Vec3(k - v.x, k - v.y, k - v.z);
}
Vec3 operator*(const Vec3& v, const double k)
{
    return Vec3(v.x * k, v.y * k, v.z * k);
}
Vec3 operator*(const double k, const Vec3& v)
{
    return v * k;
}
Vec3 operator/(const Vec3& v, const double k)
{
    return Vec3(v.x / k, v.y / k, v.z / k);
}

/// ����
double Dot(const Vec3& v1, const Vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// �O��
Vec3 Cross(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

/// ���K��
Vec3 Normalize(const Vec3& v)
{
    return v / v.length();
}

/// �R���\�[���o��
std::ostream& operator<<(std::ostream& stream, const Vec3& v)
{
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return stream;
}

/// ���K�������
void OrthonormalBasis(const Vec3& v1, Vec3& v2, Vec3& v3)
{
    if (std::abs(v1.x) > 0.9)
    {
        v2 = Vec3(0, 1, 0);
    }
    else
    {
        v2 = Vec3(1, 0, 0);
    }

    v2 = Normalize(v2 - Dot(v1, v2) * v1);
    v3 = Cross(v1, v2);
}

/// ���[���h���W�����[�J�����W
Vec3 WorldToLocal(const Vec3& v, const Vec3& s, const Vec3& t, const Vec3& n)
{
    return Vec3(Dot(v, s), Dot(v, t), Dot(v, n));
}

/// ���[�J�����W�����[���h���W
Vec3 LocalToWorld(const Vec3& v, const Vec3& s, const Vec3& t, const Vec3& n)
{
    Vec3 a = Vec3(s.x, n.x, t.x);
    Vec3 b = Vec3(s.y, n.y, t.y);
    Vec3 c = Vec3(s.z, n.z, t.z);

    return Vec3(Dot(v, a), Dot(v, b), Dot(v, c));
}

#endif // !VEC3_H_

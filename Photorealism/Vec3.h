#ifndef VEC3_H_
#define VEC3_H_

#include <iostream>
#include <cmath>

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
double dot(const Vec3& v1, const Vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// �O��
Vec3 cross(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

/// ���K��
Vec3 normalize(const Vec3& v)
{
    return v / v.length();
}

/// �R���\�[���o��
std::ostream& operator<<(std::ostream& stream, const Vec3& v)
{
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return stream;
}

#endif // !VEC3_H_

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vec3.h"
#include "Ray.h"

/// �J�������N���X
class Camera
{
public:
    Vec3 camPos;
    Vec3 camForward;
    Vec3 camRight;
    Vec3 camUp;

    Camera(const Vec3& camPos, const Vec3& camForward)
        : camPos(camPos)
        , camForward(camForward)
    {
        OrthonormalBasis(camForward, camRight, camUp);

        this->camForward    = Normalize(this->camForward);
        this->camRight      = Normalize(camRight);
        this->camUp         = Normalize(camUp);

        std::cout << "camPos: " << camPos << std::endl;
        std::cout << "camForward: " << camForward << std::endl;
        std::cout << "camRight: " << camRight << std::endl;
        std::cout << "camUp: " << camUp << std::endl;
    }

    // ���C�̎擾
    virtual Ray GetRay(double u, double v) const = 0;
};

/// �s���z�[���J����
class PinholeCamera : public Camera
{
public:
    double pinholeDist;

    PinholeCamera(const Vec3& camPos, const Vec3& camForward, double pinholeDist)
        : Camera(camPos, camForward)
        , pinholeDist(pinholeDist)
    {}

    /// ���C�̎擾
    Ray GetRay(double u, double v) const
    {
        // �s���z�[���̈ʒu
        Vec3 pinholePos = camPos + pinholeDist * camForward;
        // (u, v)�ɑ΂���Z���T��̈ʒu
        Vec3 sensorPos = camPos + u * camRight + v * camUp;

        return Ray(sensorPos, Normalize(pinholePos - sensorPos));
    }
};

/// �������Y�J����
class ThinLensCamera : public Camera
{
public:
    double a;   ///< �C���[�W�Z���T�[���烌���Y���S�܂ł̋���
    double b;   ///< �����Y���S����s���g�̍������ʂ܂ł̋���
    double f;   ///< �œ_����
    double lensRadius;  ///< �����Y�̔��a
    Vec3 lensCenter;    ///< �����Y�̒��S�ʒu

    ThinLensCamera(const Vec3& camPos, const Vec3& camForward, const Vec3& focusPoint, double a, double lensRadius)
        : Camera(camPos, camForward)
        , a(a)
        , lensRadius(lensRadius)
    {
        double cos = Dot(camForward, Normalize(focusPoint - camPos));
        b = cos * (focusPoint - camPos).length() - a;
        // �����Y�̌���
        f = 1.0 / ( 1.0 / a + 1.0 / b);
        lensCenter = camPos + a * camForward;
    }

    /// ���C�̎擾
    Ray GetRay(double u, double v) const
    {
        // �C���[�W�Z���T�[��̓_
        Vec3 sensorPos = camPos + u * camRight + v * camUp;
        // �C���[�W�Z���T�[���烌���Y���S�֌���������
        Vec3 r = Normalize(lensCenter - sensorPos);
        // �s���g�̍����ʒu
        Vec3 pf = sensorPos + (a + b) / Dot(camForward, r) * r;

        // �����Y��̓_���T���v�����O
        double x, y;
        SampleDisk(x, y);
        Vec3 l = lensCenter + lensRadius * (x * camRight + y * camUp);

        return Ray(l, Normalize(pf - l));
    }
};

#endif // !CAMERA_H_

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vec3.h"
#include "Ray.h"

/// カメラ基底クラス
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

        std::cout << "camPos: " << camPos << std::endl;
        std::cout << "camForward: " << camForward << std::endl;
        std::cout << "camRight: " << camRight << std::endl;
        std::cout << "camUp: " << camUp << std::endl;
    }

    // レイの取得
    virtual Ray GetRay(double u, double v) const = 0;
};

/// ピンホールカメラ
class PinholeCamera : public Camera
{
public:
    double pinholeDist;

    PinholeCamera(const Vec3& camPos, const Vec3& camForward, double pinholeDist)
        : Camera(camPos, camForward)
        , pinholeDist(pinholeDist)
    {}

    /// レイの取得
    Ray GetRay(double u, double v) const
    {
        // ピンホールの位置
        Vec3 pinholePos = camPos + pinholeDist * camForward;
        // (u, v)に対するセンサ上の位置
        Vec3 sensorPos = camPos + u * camRight + v * camUp;

        return Ray(sensorPos, Normalize(pinholePos - sensorPos));
    }
};

#endif // !CAMERA_H_

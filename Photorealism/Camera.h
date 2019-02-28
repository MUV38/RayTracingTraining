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

        this->camForward    = Normalize(this->camForward);
        this->camRight      = Normalize(camRight);
        this->camUp         = Normalize(camUp);

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

/// 薄レンズカメラ
class ThinLensCamera : public Camera
{
public:
    double a;   ///< イメージセンサーからレンズ中心までの距離
    double b;   ///< レンズ中心からピントの合う平面までの距離
    double f;   ///< 焦点距離
    double lensRadius;  ///< レンズの半径
    Vec3 lensCenter;    ///< レンズの中心位置

    ThinLensCamera(const Vec3& camPos, const Vec3& camForward, const Vec3& focusPoint, double a, double lensRadius)
        : Camera(camPos, camForward)
        , a(a)
        , lensRadius(lensRadius)
    {
        double cos = Dot(camForward, Normalize(focusPoint - camPos));
        b = cos * (focusPoint - camPos).length() - a;
        // レンズの公式
        f = 1.0 / ( 1.0 / a + 1.0 / b);
        lensCenter = camPos + a * camForward;
    }

    /// レイの取得
    Ray GetRay(double u, double v) const
    {
        // イメージセンサー上の点
        Vec3 sensorPos = camPos + u * camRight + v * camUp;
        // イメージセンサーからレンズ中心へ向かう方向
        Vec3 r = Normalize(lensCenter - sensorPos);
        // ピントの合う位置
        Vec3 pf = sensorPos + (a + b) / Dot(camForward, r) * r;

        // レンズ上の点をサンプリング
        double x, y;
        SampleDisk(x, y);
        Vec3 l = lensCenter + lensRadius * (x * camRight + y * camUp);

        return Ray(l, Normalize(pf - l));
    }
};

#endif // !CAMERA_H_

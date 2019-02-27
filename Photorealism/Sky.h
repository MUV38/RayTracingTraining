#ifndef SKY_H_
#define SKY_H_

#include "Vec3.h"
#include "Ray.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif // STB_IMAGE_IMPLEMENTATION

/// ��N���X
class Sky
{
public:
    /// ���ˋP�x�擾
    virtual Vec3 GetRadiance(const Ray& ray) const = 0;
};

/// �P�F��N���X
class UniformSky : public Sky
{
public:
    Vec3 color;

    UniformSky(const Vec3& color) : color(color) {}
    
    Vec3 GetRadiance(const Ray& ray) const override
    {
        return color;
    }
};

/// �V���v���ȋ�N���X
class SimpleSky : public Sky
{
public:
    SimpleSky() {}

    Vec3 GetRadiance(const Ray& ray) const override
    {
        double t = (ray.direction.y + 1.0) / 2.0;
        return (1.0 - t) * Vec3(1.0) + t * Vec3(0.7, 0.8, 1.0);
    }
};

/// IBL
class IBL : public Sky
{
public:
    int width;
    int height;
    float* hdrImage;

    IBL(const char* filename)
    {
        int n;
        hdrImage = stbi_loadf(filename, &width, &height, &n, 0);
    }

    ~IBL()
    {
        stbi_image_free(hdrImage);
    }

    Vec3 GetRadiance(const Ray& ray) const override
    {
        // ���������ʍ��W�n��
        double theta = std::acos(ray.direction.y);
        double phi = std::atan2(ray.direction.z, ray.direction.x);
        if (phi < 0) { phi += 2.0 * M_PI; }

        // (i, j)
        int i = static_cast<int>(phi / (2.0 * M_PI) * width);
        int j = static_cast<int>(theta / M_PI * height);

        // �C���f�b�N�X
        int index = 3 * i + 3 * width * j;

        return Vec3(hdrImage[index], hdrImage[index+1], hdrImage[index+2]);
    }
};

#endif // !SKY_H_

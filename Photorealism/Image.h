#ifndef IMAGE_H_
#define IMAGE_H_

#include "MathUtil.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Vec3.h"
#include "Uitl.h"

class Image
{
public:
    int width;
    int height;
    Vec3* data;

    Image(int width, int height) 
        : width(width) 
        , height(height)
    {
        data = new Vec3[width * height];
    }
    ~Image()
    {
        delete[] data;
    }

    /// ピクセル色取得
    const Vec3& GetPixel(int w, int h) const
    {
        return data[w + width * h];
    }

    /// ピクセル色設定
    void SetPixel(int w, int h, const Vec3& c)
    {
        data[w + width * h] = c;
    }

    /// ピクセル色加算
    void AddPixel(int w, int h, const Vec3& c)
    {
        data[w + width * h] += c;
    }

    /// すべてのピクセルを一定値で割る
    void Divide(double k)
    {
        for (int w = 0; w < width; ++w)
        {
            for (int h = 0; h < height; ++h)
            {
                SetPixel(w, h, GetPixel(w, h) / k);
            }
        }
    }

    /// ガンマ補正
    void GammaCorrection()
    {
        for (int w = 0; w < width; ++w)
        {
            for (int h = 0; h < height; ++h)
            {
                const auto& c = GetPixel(w, h);
                SetPixel(w, h, Vec3(std::pow(c.x, 1.0 / 2.2), std::pow(c.y, 1.0 / 2.2), std::pow(c.z, 1.0 / 2.2)));
            }
        }
    }

    /// ppm出力
    void OutputPpm(const std::string& filename) const
    {
        std::cout << "Outputting ppm..." << std::endl;

        std::ofstream file(filename);
        file << "P3" << std::endl;
        file << width << " " << height << std::endl;
        file << "255" << std::endl;
        for (int h = 0; h < height; ++h)
        {
            for (int w = 0; w < width; ++w)
            {
                const auto& c = GetPixel(w, h);
                int r = Clamp(int(255.499f * c.x), 0, 255);
                int g = Clamp(int(255.499f * c.y), 0, 255);
                int b = Clamp(int(255.499f * c.z), 0, 255);
                file << r << " " << g << " " << b << std::endl;
            }
        }
        file.close();

        std::cout << "Finished output ppm [" << filename << "]" << std::endl;
    }
};

#endif // !IMAGE_H_

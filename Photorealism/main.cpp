// Photorealism.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Vec3.h"
#include "Ray.h"
#include "Image.h"

// Vec3のテスト
void TestVec3()
{
    std::cout << "---TestVec3---" << std::endl;

    Vec3 v1(1, 2, 3), v2(4, 5, 6);

    std::cout << v1 + v2 << std::endl;
    std::cout << v1 - v2 << std::endl;
    std::cout << v1 * v2 << std::endl;
    std::cout << v1 / v2 << std::endl;

    std::cout << v1 + 1 << std::endl;
    std::cout << v1 - 1 << std::endl;
    std::cout << v1 * 2 << std::endl;
    std::cout << v1 / 2 << std::endl;

    std::cout << dot(v1, v2) << std::endl;
    std::cout << cross(v1, v2) << std::endl;

    std::cout << v1.length() << std::endl;
    std::cout << v1.length2() << std::endl;

    std::cout << "------" << std::endl;
}
// Rayのテスト
void TestRay()
{
    std::cout << "---TestRay---" << std::endl;
    
    Ray r(Vec3(0, 0, 0), Vec3(0, 0, 1));

    std::cout << r << std::endl;
    std::cout << r(10) << std::endl;

    std::cout << "------" << std::endl;
}

// Imageのテスト
void TestImage()
{
    std::cout << "---TestImage---" << std::endl;

    Image image(512, 512);

    for (int w = 0; w < image.width; ++w)
    {
        for (int h = 0; h < image.height; ++h)
        {
            image.SetPixel(w, h, Vec3(w / double(image.width), h / double(image.height), 1.0));
        }
    }
    image.OutputPpm("image_test.ppm");

    std::cout << "------" << std::endl;
}

int main()
{
    // Vec3のテスト
    TestVec3();
    // Rayのテスト
    TestRay();
    // Imageのテスト
    TestImage();

    getchar();
    return 0;
}


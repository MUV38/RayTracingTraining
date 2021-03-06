// Photorealism.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <omp.h>
#include "Vec3.h"
#include "Ray.h"
#include "Image.h"
#include "Sphere.h"
#include "Camera.h"
#include "Aggregate.h"
#include "Random.h"
#include "Sky.h"

#define ENABLE_TEST (0)

#if ENABLE_TEST
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

    std::cout << Dot(v1, v2) << std::endl;
    std::cout << Cross(v1, v2) << std::endl;

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

// Sphereテスト
void TestSphere()
{
    std::cout << "---TestSphere---" << std::endl;

    Sphere s(Vec3(0, 0, 0), 1);
    Ray ray(Vec3(0, 0, -3), Vec3(0, 0, 1));

    Hit res;
    if (s.Intersect(ray, res))
    {
        std::cout << res.hitPos << std::endl;
    }

    std::cout << "------" << std::endl;
}

// PinholeCameraテスト
void TestPinholeCamera()
{
    std::cout << "---TestPinholeCamera---" << std::endl;
    
    Image image(512, 512);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

    for (int w = 0 ; w < image.width ; ++w)
    {
        for (int h = 0; h < image.height; ++h)
        {
            double u = (2.0 * w - image.width) / image.height;
            double v = (2.0 * h - image.height) / image.height;
        
            Ray ray = cam.GetRay(-u, -v);

            Vec3 col = (ray.direction + 1.0) / 2.0;

            image.SetPixel(w, h, col);
        }
    }

    image.OutputPpm("image_test.ppm");

    std::cout << "------" << std::endl;
}
#endif // ENABLE_TEST

// 放射輝度を取得
const int MAX_DEPTH = 500;      // 最大反射回数
const double ROULETTE = 0.99;    // ロシアンルーレットの確率
Vec3 Radiance(const Ray& initRay, const Aggregate& aggregate, const Sky& sky)
{
    Vec3 col;
    Vec3 throughput(1);
    Ray ray = initRay;

    for (int depth = 0 ; depth < MAX_DEPTH ; ++depth)
    {
        Hit res;
        // レイがシーンと衝突するか
        if (aggregate.Intersect(ray, res)) 
        {
            // 法線とその正規直交基底
            Vec3 n, s, t;
            n = res.hitNormal;
            OrthonormalBasis(n, s, t);

            // 出射方向をローカル座標系に
            Vec3 woLocal = WorldToLocal(-ray.direction, s, n, t);

            // マテリアルと光源
            auto hitMaterial = res.hitSphere->material;
            auto hitLight = res.hitSphere->light;

            // Le加算
            col += throughput * hitLight->Le();

            // 方向のサンプリングとBRDFの評価
            Vec3 brdf;
            Vec3 wiLocal;
            double pdf;
            brdf = hitMaterial->Sample(woLocal, wiLocal, pdf);

            // コサイン
            double cos = AbsCosTheta(wiLocal);

            // サンプリング方向をワールド座標系に
            Vec3 wi = LocalToWorld(wiLocal, s, n, t);

            // スループット更新
            throughput *= brdf * cos / pdf;

            // 次のレイ
            ray = Ray(res.hitPos, wi);
        }
        else
        {
            // 空に飛んで行った
            col += throughput * sky.GetRadiance(ray);
            break;
        }

        // ロシアンルーレット
        if (Rnd() >= ROULETTE) 
        { 
            break;
        }
        else
        {
            throughput /= ROULETTE;
        }
    }
    return col;
}

// メインシーン
void MainScene()
{
    // スパーサンプリング数
    const int N = 200;

    Image image(512, 512);
    ThinLensCamera cam(Vec3(0, 0, 1), Vec3(0, 0, -1), Vec3(0, 0, -3), 1, 0.1);

    auto mat1 = std::make_shared<Diffuse>(Vec3(0.9));
    auto mat2 = std::make_shared<Glass>(1.5);

    auto light1 = std::make_shared<Light>(Vec3(0));

    Aggregate aggregate;
    aggregate.Add(std::make_shared<Sphere>(Vec3(0, -10001, 0), 10000, mat1, light1));
    aggregate.Add(std::make_shared<Sphere>(Vec3(0, 0, -3), 1, mat2, light1));

    IBL sky("PaperMill_E.hdr");

    #pragma omp parallel for schedule(dynamic, 1)
    for (int w = 0; w < image.width; ++w)
    {
        for (int h = 0; h < image.height; ++h)
        {
            for (int s = 0; s < N; ++s)
            {
                double u = (2.0 * ((double)w + Rnd()) - (double)image.width) / (double)image.height;
                double v = (2.0 * ((double)h + Rnd()) - (double)image.height) / (double)image.height;

                Ray ray = cam.GetRay(-u, -v);

                // 放射輝度を計算
                Vec3 col = Radiance(ray, aggregate, sky);

                // サンプルを加算
                image.AddPixel(w, h, col);
            }
            
            // 進捗状況を出力
            if (omp_get_thread_num() == 0)
            {
                std::cout << double(h + w * image.height) / (image.width * image.height) * 100 << "\r" << std::flush;
            }
        }
    }

    // サンプリング数で割る
    image.Divide(N);

    // ガンマ補正
    image.GammaCorrection();

    image.OutputPpm("path_tracing.ppm");
}

int main()
{
#if ENABLE_TEST
    // Vec3のテスト
    TestVec3();
    // Rayのテスト
    TestRay();
    // Imageのテスト
    TestImage();
    // Sphereのテスト
    TestSphere();
    // PinholeCameraテスト
    TestPinholeCamera();
#endif // ENABLE_TEST

    // メインシーン
    MainScene();

    return 0;
}


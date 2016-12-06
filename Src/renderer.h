#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "material.h"
#include "ppm.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "monte_carlo_ray_tracer.h"

#ifdef _OPENMP
#include <omp.h>
#endif // _OPENMP

namespace Renderer
{

void Render(const std::string& filename, int width, int height)
{
#ifdef _OPENMP
	omp_set_num_threads(8);
#endif // _OPENMP

	const Vec camera_position = Vec(0, 30, 150);
	const Vec camera_dir      = normalize(Vec(0.0, -0.3, -1.0));
	const Vec camera_up       = normalize(Vec(0.0, 1.0, 0.0));

	const double screen_width = 100.0 * (width / static_cast<double>(height));
	const double screen_height = 100.0;
	const double screen_dist  = camera_position.z; // 常にZ=0の所にスクリーンを貼る

	const Vec screen_x = normalize(cross(camera_up, camera_dir));
	const Vec screen_y = normalize(cross(camera_dir, screen_x));
	const Vec screen_center = camera_position + camera_dir * screen_dist;

	// 世界の定義
	World world;
	{
		Sphere* sphere = new Sphere(new LambertianMaterial(Color(1, 1, 1)));
		sphere->pos = Vec(25, 20, 20);
		sphere->radius = 20;
		world.AddObject(sphere);

		Sphere* sphere2 = new Sphere(new LambertianMaterial(Color(1, 1, 1)));
		sphere2->pos = Vec(-25, 20, 20);
		sphere2->radius = 20;
		world.AddObject(sphere2);

		Sphere* sphere3 = new Sphere(new LambertianMaterial(Color(1, 1, 1)));
		sphere3->pos = Vec(-20, -100000, 20);
		sphere3->radius = 100000.0;
		world.AddObject(sphere3);

		//Plane* plane = new Plane(new LambertianMaterial(Color(1, 1, 0)));
		//plane->normal = Vec(0, 1, 0);
		//plane->pos = Vec(0, 0, 0);
		//world.AddObject(plane);

		//Sphere* light1 = new Sphere(new LightSource(Color(1, 1, 1)));
		//light1->pos = Vec(0, 50, 20);
		//light1->radius = 10;
		//world.AddObject(light1);
	}

	MonteCarloRayTracer tracer(&world);


	Color* image = new Color[width*height];

	int num_subpixel = 1;
	int num_sample_per_subpixel = 16;

	for(int h=0 ; h<height ; h++){
		std::cerr << "Rendering (h = " << h << ") " << (100.0 * h / (height - 1)) << "%" << std::endl;
#pragma omp parallel for schedule(static) // OpenMP
		for(int w=0 ; w<width ; w++){
			Random random(h * width + w + 1);
			const int image_index = (height - h - 1) * width + w;
			image[image_index] = Color(0, 0, 0);
			Color color = Color(0, 0, 0);

			// num_subpixel x num_subpixel のスーパーサンプリング。
			//for (int sy = 0; sy < num_subpixel; ++sy) {
				//for (int sx = 0; sx < num_subpixel; ++sx) {

					// 一つのピクセルあたりsamples回サンプリングする。
					for (int s = 0; s < num_sample_per_subpixel; s++) {
#if 1
						// スクリーン座標（-1.0～1.0）を求める
						double half_width = static_cast<double>(width) * 0.5;
						double half_height = static_cast<double>(height) * 0.5;
						double rate_screen_x = ((w + 1.0) - half_width) / half_width;
						double rate_screen_y = ((h + 1.0) - half_height) / half_height;

						// スクリーン上の位置
						Vec screen_position = 
							screen_center + 
							(screen_x * (screen_width * rate_screen_x)) +
							(screen_y * (screen_height * rate_screen_y));
#else
						const double rate = (1.0 / num_subpixel);
						const double r1 = sx * rate + rate / 2.0;
						const double r2 = sy * rate + rate / 2.0;
						// イメージセンサー上の位置。
						const Vec screen_position =
							screen_center +
							screen_x * ((r1 + w) / width - 0.5) +
							screen_y * ((r2 + h) / height - 0.5);
#endif
						// レイ
						Ray ray;
						ray.origin = camera_position;
						ray.direction = normalize(screen_position - camera_position);

						// 背景色
						//Color backgroundColor(0, 0, 0);
						//{
						//	double t = 0.5 * ray.direction.y + 1.0;
						//	backgroundColor = (1.0 - t) * Vec(1.0, 1.0, 1.0) + t * Vec(0.5, 0.7, 1.0);
						//	world.SetBackgroundColor(backgroundColor);
						//}

						color = color + tracer.TraceRay(ray, random, 0) / num_sample_per_subpixel;
					}
				//}
				image[image_index] = image[image_index] + color;
			//}
		}
	}

	// 出力
	save_ppm_file(filename, image, width, height);

	delete [] image;
	image = nullptr;
}

}

#endif // !_RENDERER_H_

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
#if 1
void Render(const std::string& filename, int width, int height)
{
#ifdef _OPENMP
	omp_set_num_threads(8);
#endif // _OPENMP

	const Vec camera_position = Vec(0, 40, 400);
	const Vec camera_dir      = normalize(Vec(0.0, 0, -1.0));
	const Vec camera_up       = normalize(Vec(0.0, 1.0, 0.0));

	const double screen_width = 80.0 * (width / static_cast<double>(height));
	const double screen_height = 80.0;
	const double screen_dist  = camera_position.z; // 常にZ=0の所にスクリーンを貼る

	const Vec screen_x = normalize(cross(camera_up, camera_dir));
	const Vec screen_y = normalize(cross(camera_dir, screen_x));
	const Vec screen_center = camera_position + camera_dir * screen_dist;

	// 世界の定義
	World world;
	{
		// コーネルボックス
		{
			const double BOX_SIZE = 80.0;
			const double HALF_BOX_SIZE = BOX_SIZE * 0.5;
			
			// 下
			Sphere* box1 = new Sphere(new LambertianMaterial(Color(1, 1, 1)));
			box1->pos = Vec(0, -100000.0, 0);
			box1->radius = 100000.0;
			world.AddObject(box1);

			// 上
			Sphere* box2 = new Sphere(new LambertianMaterial(Color(1, 1, 1)));
			box2->pos = Vec(0, 100000.0 + BOX_SIZE, 0);
			box2->radius = 100000.0;
			world.AddObject(box2);

			// 左
			Sphere* box3 = new Sphere(new LambertianMaterial(Color(1, 0, 0)));
			box3->pos = Vec(-100000-BOX_SIZE, HALF_BOX_SIZE, 0);
			box3->radius = 100000.0;
			world.AddObject(box3);

			// 右
			Sphere* box4 = new Sphere(new LambertianMaterial(Color(0, 1, 0)));
			box4->pos = Vec(100000+BOX_SIZE, HALF_BOX_SIZE, 0);
			box4->radius = 100000.0;
			world.AddObject(box4);

			// 正面
			Sphere* box5 = new Sphere(new LambertianMaterial(Color(1, 1, 1)));
			box5->pos = Vec(0, HALF_BOX_SIZE, 100000+ HALF_BOX_SIZE);
			box5->radius = 100000.0;
			world.AddObject(box5);
		}

		Sphere* sphere = new Sphere(new LambertianMaterial(Color(0, 1, 1)));
		sphere->pos = Vec(25, 20, 0);
		sphere->radius = 20;
		world.AddObject(sphere);

		Sphere* sphere2 = new Sphere(new LambertianMaterial(Color(1, 1, 0)));
		sphere2->pos = Vec(-25, 20, 0);
		sphere2->radius = 20;
		world.AddObject(sphere2);

		//Plane* plane = new Plane(new LambertianMaterial(Color(1, 1, 0)));
		//plane->normal = Vec(0, 1, 0);
		//plane->pos = Vec(0, 0, 0);
		//world.AddObject(plane);

		Sphere* light1 = new Sphere(new LightSource(Color(1, 1, 1)));
		light1->pos = Vec(0, 70, 0);
		light1->radius = 10;
		world.AddObject(light1);
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
						double rate_screen_x = ((static_cast<double>(w) + 1.0) - half_width) / half_width;
						double rate_screen_y = ((static_cast<double>(h) + 1.0) - half_height) / half_height;

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

						// レイトレース
						color = color + tracer.TraceRay(ray, random, 0) 
							/ static_cast<double>(num_sample_per_subpixel)/* / (double)(num_subpixel * num_subpixel)*/;
					}
					image[image_index] = image[image_index] + color;
				//}
			//}
		}
	}

	// 出力
	save_ppm_file(filename, image, width, height);

	delete [] image;
	image = nullptr;
}
#else
int Render(const char *filename, const int width, const int height) {
#ifdef _OPENMP
	omp_set_num_threads(8);
#endif // _OPENMP

	// 世界の定義
	World world;
	{
		// コーネルボックス
		{
			const double BOX_SIZE = 80.0;
			const double HALF_BOX_SIZE = BOX_SIZE * 0.5;

			// 下
			Sphere* box1 = new Sphere(new LambertianMaterial(Color(1, 1, 1)));
			box1->pos = Vec(0, -100000, 0);
			box1->radius = 100000.0;
			world.AddObject(box1);

			// 上
			Sphere* box2 = new Sphere(new LambertianMaterial(Color(1, 1, 1)));
			box2->pos = Vec(0, 100000.0 + BOX_SIZE, 0);
			box2->radius = 100000.0;
			world.AddObject(box2);

			// 左
			Sphere* box3 = new Sphere(new LambertianMaterial(Color(1, 0, 0)));
			box3->pos = Vec(-100000 - BOX_SIZE, HALF_BOX_SIZE, 0);
			box3->radius = 100000.0;
			world.AddObject(box3);

			// 右
			Sphere* box4 = new Sphere(new LambertianMaterial(Color(0, 1, 0)));
			box4->pos = Vec(100000 + BOX_SIZE, HALF_BOX_SIZE, 0);
			box4->radius = 100000.0;
			world.AddObject(box4);

			// 正面
			Sphere* box5 = new Sphere(new LambertianMaterial(Color(1, 1, 1)));
			box5->pos = Vec(0, HALF_BOX_SIZE, 100000 + 50);
			box5->radius = 100000.0;
			world.AddObject(box5);
		}

		Sphere* sphere = new Sphere(new LambertianMaterial(Color(0, 1, 1)));
		sphere->pos = Vec(25, 10, 20);
		sphere->radius = 20;
		world.AddObject(sphere);

		Sphere* sphere2 = new Sphere(new LambertianMaterial(Color(1, 1, 0)));
		sphere2->pos = Vec(-25, 10, 20);
		sphere2->radius = 20;
		world.AddObject(sphere2);

		//Plane* plane = new Plane(new LambertianMaterial(Color(1, 1, 0)));
		//plane->normal = Vec(0, 1, 0);
		//plane->pos = Vec(0, 0, 0);
		//world.AddObject(plane);

		Sphere* light1 = new Sphere(new LightSource(Color(1, 1, 1)));
		light1->pos = Vec(0, 80, 20);
		light1->radius = 10;
		world.AddObject(light1);
	}

	MonteCarloRayTracer tracer(&world);

	int num_sample_per_subpixel = 16;
	int num_subpixel = 1;

	// カメラ位置。
	const Vec camera_position = Vec(0, 25, 1000);
	const Vec camera_lookat = Vec(0.0, 25, 0.0);
	const Vec camera_dir = normalize(camera_lookat - camera_position);
	const Vec camera_up = Vec(0.0, 1.0, 0.0);

	// ワールド座標系でのイメージセンサーの大きさ。
	const double sensor_width = 200.0 * width / height; // アスペクト比調整。
	const double sensor_height = 200.0;
	// イメージセンサーまでの距離。
	const double sensor_dist = camera_position.z;
	// イメージセンサーを張るベクトル。
	const Vec sensor_x_vec = normalize(cross(camera_dir, camera_up)) * sensor_width;
	const Vec sensor_y_vec = normalize(cross(sensor_x_vec, camera_dir)) * sensor_height;
	const Vec sensor_center = camera_position + camera_dir * sensor_dist;

	Color *image = new Color[width * height];
	std::cout << width << "x" << height << " " << num_sample_per_subpixel * (num_subpixel * num_subpixel) << " spp" << std::endl;

	for (int y = 0; y < height; ++y) {
		std::cerr << "Rendering (y = " << y << ", " << (100.0 * y / (height - 1)) << " %)          \r";
#pragma omp parallel for schedule(static) // OpenMP
		for (int x = 0; x < width; ++x) {
			Random random(y * width + x + 1);

			const int image_index = (height - y - 1) * width + x;
			// num_subpixel x num_subpixel のスーパーサンプリング。
			for (int sy = 0; sy < num_subpixel; ++sy) {
				for (int sx = 0; sx < num_subpixel; ++sx) {
					Color accumulated_radiance = Color();
					// 一つのサブピクセルあたりsamples回サンプリングする。
					for (int s = 0; s < num_sample_per_subpixel; s++) {
						const double rate = (1.0 / num_subpixel);
						const double r1 = sx * rate + rate / 2.0;
						const double r2 = sy * rate + rate / 2.0;
						// イメージセンサー上の位置。
						const Vec position_on_sensor =
							sensor_center +
							sensor_x_vec * ((r1 + x) / width - 0.5) +
							sensor_y_vec * ((r2 + y) / height - 0.5);
						// レイを飛ばす方向。
						const Vec dir = normalize(position_on_sensor - camera_position);

						accumulated_radiance = accumulated_radiance +
							tracer.TraceRay(Ray(camera_position, dir), random, 0)
							/ (double)num_sample_per_subpixel / (double)(num_subpixel * num_subpixel);
					}
					image[image_index] = image[image_index] + accumulated_radiance;
				}
			}
		}
	}
	std::cout << std::endl;

	// 出力
	save_ppm_file(filename, image, width, height);
	delete[] image;

	return 0;
}
#endif
}

#endif // !_RENDERER_H_

/**
* @file my_renderer.cpp
* @brief レンダラーの定義
* @author Toru Miyawaki
*/

#include <iostream>
#include <cfloat>

#include "my_renderer.h"
#include "my_intersect.h"
#include "my_ray.h"
#include "my_sphere.h"
#include "my_plane.h"

#include "../ppm.h"
#include "../material.h"

#include "my_world.h"
#include "TestTracer.h"

using namespace edupt;

namespace My{
	// レンダラー実行
	void Renderer(int width, int height){
		const Vec camera_position = Vec(0, 10, 100);
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
			Sphere* sphere = new Sphere();
			sphere->pos = Vec(20, 0, 20);
			sphere->radius = 20;
			sphere->color = Vec(1, 1, 1);
			world.AddObject(sphere);

			Sphere* sphere2 = new Sphere();
			sphere2->pos = Vec(-20, 0, 20);
			sphere2->radius = 20;
			sphere2->color = Vec(1, 0, 0);
			world.AddObject(sphere2);

			Plane* plane = new Plane();
			plane->normal = Vec(0, 1, 0);
			plane->pos = Vec(0, 0, 0);
			plane->color = Vec(1, 1, 0);
			world.AddObject(plane);
		}

		TestTracer tracer(&world);

		Color *image = new Color[width * height];

		for(int y=0 ; y<height ; y++){
			std::cerr << "Rendering (y = " << y << ") " << (100.0 * y / (height - 1)) << "%" << std::endl;
			for(int x=0 ; x<width ; x++){
				const int image_index = (height - y - 1) * width + x;
				Color color(0, 0, 0);

				// スクリーン座標（-1.0～1.0）を求める
				double half_width = static_cast<double>(width) * 0.5;
				double half_height = static_cast<double>(height) * 0.5;
				double rate_screen_x = ((x + 1.0) - half_width) / half_width;
				double rate_screen_y = ((y + 1.0) - half_height) / half_height;

				// スクリーン上の位置
				Vec screen_position = 
					screen_center + 
					(screen_x * (screen_width * rate_screen_x)) +
					(screen_y * (screen_height * rate_screen_y));

				// レイ
				Ray ray;
				ray.origin = camera_position;
				ray.direction = normalize(screen_position - camera_position);

				// 背景色
				{
					double t = 0.5 * ray.direction.y + 1.0;
					Color backgroundColor = (1.0 - t) * Vec(1.0, 1.0, 1.0) + t * Vec(0.5, 0.7, 1.0);
					world.SetBackgroundColor(backgroundColor);
				}

				image[image_index] = tracer.TraceRay(ray, FLT_MAX);
			}
		}

		// ポストエフェクト
		//for(int y=0 ; y<height ; y++){
		//	for(int x=0 ; x<width ; x++){
		//		const int image_index = (height - y - 1) * width + x;

		//		Color c = image[image_index];
		//		double gray = (c.x + c.y + c.z) / 3.0;

		//		image[image_index] = Color(gray, gray, gray);
		//	}
		//}

		// 出力
		save_ppm_file(std::string("image.ppm"), image, width, height);

		delete [] image;
		image = nullptr;
	}
};
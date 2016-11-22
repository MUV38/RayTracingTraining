#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "material.h"
#include "ppm.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "monte_carlo_ray_tracer.h"

namespace Renderer
{

void Render(const std::string& filename, int width, int height)
{
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
		sphere->material.albedo = Color(0, 1, 0);
		world.AddObject(sphere);

		Sphere* sphere2 = new Sphere();
		sphere2->pos = Vec(-20, 0, 20);
		sphere2->radius = 20;
		sphere2->material.albedo = Color(1, 0, 0);
		world.AddObject(sphere2);

		Plane* plane = new Plane();
		plane->normal = Vec(0, 1, 0);
		plane->pos = Vec(0, 0, 0);
		plane->material.albedo = Color(1, 1, 0);
		world.AddObject(plane);
	}

	MonteCarloRayTracer tracer(&world);


	Color* image = new Color[width*height];

	for(int h=0 ; h<height ; h++){
		std::cerr << "Rendering (h = " << h << ") " << (100.0 * h / (height - 1)) << "%" << std::endl;
		for(int w=0 ; w<width ; w++){
			const int image_index = (height - h - 1) * width + w;

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

			// レイ
			Ray ray;
			ray.origin = camera_position;
			ray.direction = normalize(screen_position - camera_position);

			// 背景色
			Color backgroundColor(0, 0, 0);
			{
				double t = 0.5 * ray.direction.y + 1.0;
				backgroundColor = (1.0 - t) * Vec(1.0, 1.0, 1.0) + t * Vec(0.5, 0.7, 1.0);
				world.SetBackgroundColor(backgroundColor);
			}

			image[image_index] = tracer.TraceRay(ray);
		}
	}

	// 出力
	save_ppm_file(filename, image, width, height);

	delete [] image;
	image = nullptr;
}

}

#endif // !_RENDERER_H_

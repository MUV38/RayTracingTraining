#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cfloat>
#include <chrono>
#include <omp.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "sphere.h"
#include "moving_sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "util.h"
#include "material.h"
#include "texture.h"

#define RANDOM_SCENE (0)
#define TWO_SPHERE_SCENE (1)

#if RANDOM_SCENE
#define ENABLE_RANDOM_SCENE (1)
#elif TWO_SPHERE_SCENE
#define ENABLE_TWO_SPHERE_SCENE (1)
#endif

vec3 color(const ray& r, hitable* world, int depth){
	hit_record rec;
	if(world->hit(r, 0.001, FLT_MAX, rec)){
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            return attenuation * color(scattered, world, depth+1);
        }else{
            return vec3(0, 0, 0);
        }
	}else{
		vec3 unit_direction = unit_vector(r.direction());
		double t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0-t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

hitable* random_scene() 
{
    int n = 500;
    hitable** list = new hitable*[n+1];

    texture* checker = new checker_texture(
        new constant_texture(vec3(0.2, 0.3, 0.1)),
        new constant_texture(vec3(0.9, 0.9, 0.9))
    );
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(checker));
    
    int i = 1;
    for (int a=-11 ; a<11 ; a++) {
        for (int b=-11 ; b<11 ; b++) {
            float choose_mat = drand48();
            vec3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) { // diffuse
                    list[i++] = new moving_sphere(
                        center, 
                        center + vec3(0, 0.5 * drand48(), 0),
                        0.0, 
                        1.0,
                        0.2, 
                        new lambertian(new constant_texture(vec3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())))
                    );
                }
            }
            else if (choose_mat < 0.95) { // metal
                list[i++] = new sphere(
                    center, 
                    0.2,
                    new metal(vec3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48())
                );
            }
            else  { // glass
                list[i++] = new sphere(center, 0.2, new dielectric(1.5));
            }
        }
    }
    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(new constant_texture(vec3(0.4, 0.2, 0.1))));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hitable_list(list, i);
}

hitable* two_spheres()
{
    // load image
    int nx, ny, nn;
    unsigned char* tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);

    texture* pertext = new noise_texture(5);
    hitable** list = new hitable*[2];
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(pertext));
    //list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(pertext));
    list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(new image_texture(tex_data, nx, ny)));

    return new hitable_list(list, 2);
}

int main(){
	std::ofstream ofs;
	ofs.open("image.ppm", std::ios::out|std::ios::trunc);
	
	const int nx = 360;
	const int ny = 180;
	int ns = 10;
	std::cout << "write ppm image\n" << "w:" << nx << " " << "h:" << ny << "\n";
	ofs << "P3\n" << nx << " " << ny << "\n255\n";
		
	//hitable* list[5];
 //   list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5))); 
 //   list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0))); 
 //   list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3)); 
 //   list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
 //   list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));

	//hitable* world = new hitable_list(list, 5);
#if ENABLE_RANDOM_SCENE
    hitable* world = random_scene();

    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus, 0.0, 1.0);
#elif ENABLE_TWO_SPHERE_SCENE
    hitable* world = two_spheres();

    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;
    camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus, 0.0, 1.0);
#endif

    auto start_time = std::chrono::system_clock::now();

    int out_color[nx * ny * 3];
	for(int j=ny-1 ; j>=0 ; j--){
		std::cout << "writing y = " << j << "\n";
        #pragma omp parallel for
		for(int i=0 ; i<nx ; i++){
			vec3 col(0, 0, 0);
			for(int s=0 ; s<ns ; s++){
				double u = double(i+drand48()) / double(nx);
				double v = double(j+drand48()) / double(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}
			col /= double(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
            out_color[j * nx * 3 + i * 3 + 0] = ir;
            out_color[j * nx * 3 + i * 3 + 1] = ig;
            out_color[j * nx * 3 + i * 3 + 2] = ib;
		}
	}

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i<nx; i++) {
            auto* col = &out_color[j * nx * 3 + i * 3];
            ofs << col[0] << " " << col[1] << " " << col[2] << "\n";
        }
    }

    auto end_time = std::chrono::system_clock::now();
    auto duration = end_time - start_time;
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0;

    std::cout << "RenderTime[sec]:" << elapsed << std::endl;

	system("open_image.bat");
}
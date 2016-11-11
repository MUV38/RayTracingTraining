#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "material.h"
#include "ppm.h"

namespace Renderer
{

void Render(const std::string& filename, int width, int height)
{
	Color* image = new Color[width*height];

	for(int h=0 ; h<height ; h++){
		for(int w=0 ; w<width ; w++){
			image[h*width + w] = Color(1, 0, 0);
		}
	}

	save_ppm_file(filename, image, width, height);

	delete [] image;
}

}

#endif // !_RENDERER_H_

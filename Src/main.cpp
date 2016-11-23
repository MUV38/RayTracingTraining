#include <iostream>

#include "renderer.h"

int	main()
{
	Renderer::Render("image.ppm", 640, 480);

	system("open_ppm.bat");

	return 0;
}
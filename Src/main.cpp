#include <iostream>

#include "renderer.h"

int	main()
{
	Renderer::Render("image.ppm", 512, 512);

	system("open_ppm.bat");

	return 0;
}
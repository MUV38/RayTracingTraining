#include <iostream>

#include "renderer.h"

int	main()
{
	Renderer::Render("image.ppm", 200, 200);

	system("open_ppm.bat");

	return 0;
}
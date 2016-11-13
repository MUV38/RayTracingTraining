#include <iostream>
#include <cstdlib>

#include "render.h"
#include "My/my_renderer.h"

int main(int argc, char **argv) {
	std::cout << "test renderer" << std::endl << std::endl;

	// 640x480の画像、(2x2) * 4 sample / pixel
	//edupt::render(640, 480, 8, 16);

	My::Renderer(640, 480);

	// PPMビューワーを自動で呼び出す
	system("open_ppm.bat");
}

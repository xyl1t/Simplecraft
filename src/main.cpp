#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "game.hpp"
#include <ctime>

int main(int argc, char** argv) {
	
	srand(time(NULL));

	Game game { };

	game.Run();
	
	return 0;
}
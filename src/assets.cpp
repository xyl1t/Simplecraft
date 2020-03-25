#include "assets.hpp"

#include <stb/stb_image.h>
#include <algorithm>

Assets::Assets() : textureWidth(0), textureHeight(0), blockVerts{ }, blockTextures { } { }
Assets::~Assets() { }

void Assets::LoadAssets() {
	// lambda to make code cleaner
	auto loadTexture = [&](std::string name, std::string filePath) {
		int c;
		uint8_t* textureData = stbi_load(filePath.c_str(), &textureWidth, &textureHeight, &c, 0);
		textures[name] = textureData;
	};

	// loading textures
	loadTexture("grass",		"assets/textures/grass.png");
	loadTexture("dirt",			"assets/textures/dirt.png");
	loadTexture("cobblestone",	"assets/textures/cobblestone.png");
	loadTexture("sand",			"assets/textures/sand.png");
	loadTexture("water",		"assets/textures/water.png");
	loadTexture("stone",		"assets/textures/stone.png");
	loadTexture("plank",		"assets/textures/plank.png");
	loadTexture("glowstone",	"assets/textures/glowstone.png");

	// loading textures (differnt way of accessing them)
	blockTextures[AIR_BLOCK] = nullptr;
	blockTextures[GRASS_BLOCK] = textures["grass"];
	blockTextures[DIRT_BLOCK] = textures["dirt"];
	blockTextures[COBBLESTONE_BLOCK] = textures["cobblestone"];
	blockTextures[SAND_BLOCK] = textures["sand"];
	blockTextures[WATER_BLOCK] = textures["water"];
	blockTextures[STONE_BLOCK] = textures["stone"];
	blockTextures[PLANK_BLOCK] = textures["plank"];
	blockTextures[GLOWSTONE_BLOCK] = textures["glowstone"];
	// texture coordiantes 
	float w0 = (textureWidth / 4.f) * 0 / (float)textureWidth;
	float w1 = (textureWidth / 4.f) * 1 / (float)textureWidth;
	float w2 = (textureWidth / 4.f) * 2 / (float)textureWidth;
	float w3 = (textureWidth / 4.f) * 3 / (float)textureWidth;
	float w4 = (textureWidth / 4.f) * 4 / (float)textureWidth;

	float h0 = (textureHeight / 3.f) * 0 / (float)textureHeight;
	float h1 = (textureHeight / 3.f) * 1 / (float)textureHeight;
	float h2 = (textureHeight / 3.f) * 2 / (float)textureHeight;
	float h3 = (textureHeight / 3.f) * 3 / (float)textureHeight;

	const int blockVertsSize = sizeof(blockVerts) / sizeof(blockVerts[0]);

	// loading block vertices
	float vertices[blockVertsSize] = {
		/* vertices */		   /* normals */		  /* colors */		   /* tex */

		// top face
		-0.5f, +0.5f, -0.5f,   +0.0f, +1.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w1, h0, 0.0f, // top left -x -z
		-0.5f, +0.5f, +0.5f,   +0.0f, +1.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w1, h1, 1.0f, // bottom left -x +z
		+0.5f, +0.5f, +0.5f,   +0.0f, +1.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w2, h1, 2.0f, // bottom right +x +z
		+0.5f, +0.5f, -0.5f,   +0.0f, +1.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w2, h0, 3.0f, // top right +x -z

		// bottom face									  
		-0.5f, -0.5f, -0.5f,   +0.0f, -1.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w1, h2, 0.0f, // top left -x -z
		-0.5f, -0.5f, +0.5f,   +0.0f, -1.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w1, h3, 1.0f, // bottom left -x +z
		+0.5f, -0.5f, +0.5f,   +0.0f, -1.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w2, h3, 2.0f, // bottom right +x +z
		+0.5f, -0.5f, -0.5f,   +0.0f, -1.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w2, h2, 3.0f, // top right +x -z

		// left side									  
		-0.5f, +0.5f, -0.5f,   -1.0f, +0.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w0, h1, 0.0f, // top left
		-0.5f, -0.5f, -0.5f,   -1.0f, +0.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w0, h2, 1.0f, // bottom left
		-0.5f, -0.5f, +0.5f,   -1.0f, +0.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w1, h2, 2.0f, // bottom right
		-0.5f, +0.5f, +0.5f,   -1.0f, +0.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w1, h1, 3.0f, // top right

		// front			  							  
		-0.5f, +0.5f, +0.5f,   +0.0f, +0.0f, +1.0f,   1.0f, 1.0f, 1.0f,   w1, h1, 0.0f, // top left
		-0.5f, -0.5f, +0.5f,   +0.0f, +0.0f, +1.0f,   1.0f, 1.0f, 1.0f,   w1, h2, 1.0f, // bottom left
		+0.5f, -0.5f, +0.5f,   +0.0f, +0.0f, +1.0f,   1.0f, 1.0f, 1.0f,   w2, h2, 2.0f, // bottom right
		+0.5f, +0.5f, +0.5f,   +0.0f, +0.0f, +1.0f,   1.0f, 1.0f, 1.0f,   w2, h1, 3.0f, // top right

		// right side								 	  
		+0.5f, +0.5f, -0.5f,   +1.0f, +0.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w2, h1, 0.0f, // top left
		+0.5f, -0.5f, -0.5f,   +1.0f, +0.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w2, h2, 1.0f, // bottom left
		+0.5f, -0.5f, +0.5f,   +1.0f, +0.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w3, h2, 2.0f, // bottom right
		+0.5f, +0.5f, +0.5f,   +1.0f, +0.0f, +0.0f,   1.0f, 1.0f, 1.0f,   w3, h1, 3.0f, // top right

		// behind			  						 	  
		-0.5f, +0.5f, -0.5f,   +0.0f, +0.0f, -1.0f,   1.0f, 1.0f, 1.0f,   w3, h1, 0.0f, // top left
		-0.5f, -0.5f, -0.5f,   +0.0f, +0.0f, -1.0f,   1.0f, 1.0f, 1.0f,   w3, h2, 1.0f, // bottom left
		+0.5f, -0.5f, -0.5f,   +0.0f, +0.0f, -1.0f,   1.0f, 1.0f, 1.0f,   w4, h2, 2.0f, // bottom right
		+0.5f, +0.5f, -0.5f,   +0.0f, +0.0f, -1.0f,   1.0f, 1.0f, 1.0f,   w4, h1, 3.0f, // top right
	};	
	std::copy(vertices, vertices + blockVertsSize, blockVerts);

	int indices[36] = {
		  0,  1,  2,    0,  2,  3, // top
		  6,  5,  4,    7,  6,  4, // bottom
		  8,  9, 10,    8, 10, 11, // left
		 12, 13, 14,   12, 14, 15, // front
		 18, 17, 16,   19, 18, 16, // right
		 22, 21, 20,   23, 22, 20, // behind
	};
	std::copy(indices, indices + 36, blockIndis);
}

void Assets::UnloadAssets() {
	for (const auto& x : textures) {
		stbi_image_free(x.second);
	}
}

#if 0
// loading block vertices
float vertices[264] = {
	/* vertices */		   /* normals */		  /* colors */		   /* tex */

	// top face
	-0.5f, +0.5f, -0.5f,   +0.0f, +1.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w1, h0, // top left -x -z
	-0.5f, +0.5f, +0.5f,   +0.0f, +1.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w1, h1, // bottom left -x +z
	+0.5f, +0.5f, +0.5f,   +0.0f, +1.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w2, h1, // bottom right +x +z
	+0.5f, +0.5f, -0.5f,   +0.0f, +1.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w2, h0, // top right +x -z

	// bottom face									  
	-0.5f, -0.5f, -0.5f,   +0.0f, -1.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w1, h2, // top left -x -z
	-0.5f, -0.5f, +0.5f,   +0.0f, -1.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w1, h3, // bottom left -x +z
	+0.5f, -0.5f, +0.5f,   +0.0f, -1.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w2, h3, // bottom right +x +z
	+0.5f, -0.5f, -0.5f,   +0.0f, -1.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w2, h2, // top right +x -z

	// left side									  
	-0.5f, +0.5f, -0.5f,   -1.0f, +0.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w0, h1, // top left
	-0.5f, -0.5f, -0.5f,   -1.0f, +0.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w0, h2, // bottom left
	-0.5f, -0.5f, +0.5f,   -1.0f, +0.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w1, h2, // bottom right
	-0.5f, +0.5f, +0.5f,   -1.0f, +0.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w1, h1, // top right

	// front			  							  
	-0.5f, +0.5f, +0.5f,   +0.0f, +0.0f, +1.0f,   0.0f, 0.0f, 0.0f,   w1, h1, // top left
	-0.5f, -0.5f, +0.5f,   +0.0f, +0.0f, +1.0f,   0.0f, 0.0f, 0.0f,   w1, h2, // bottom left
	+0.5f, -0.5f, +0.5f,   +0.0f, +0.0f, +1.0f,   0.0f, 0.0f, 0.0f,   w2, h2, // bottom right
	+0.5f, +0.5f, +0.5f,   +0.0f, +0.0f, +1.0f,   0.0f, 0.0f, 0.0f,   w2, h1, // top right

	// right side									  
	+0.5f, +0.5f, -0.5f,   +1.0f, +0.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w2, h1, // top left
	+0.5f, -0.5f, -0.5f,   +1.0f, +0.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w2, h2, // bottom left
	+0.5f, -0.5f, +0.5f,   +1.0f, +0.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w3, h2, // bottom right
	+0.5f, +0.5f, +0.5f,   +1.0f, +0.0f, +0.0f,   0.0f, 0.0f, 0.0f,   w3, h1, // top right

	// behind			  							  
	-0.5f, +0.5f, -0.5f,   +0.0f, +0.0f, -1.0f,   0.0f, 0.0f, 0.0f,   w3, h1, // top left
	-0.5f, -0.5f, -0.5f,   +0.0f, +0.0f, -1.0f,   0.0f, 0.0f, 0.0f,   w3, h2, // bottom left
	+0.5f, -0.5f, -0.5f,   +0.0f, +0.0f, -1.0f,   0.0f, 0.0f, 0.0f,   w4, h2, // bottom right
	+0.5f, +0.5f, -0.5f,   +0.0f, +0.0f, -1.0f,   0.0f, 0.0f, 0.0f,   w4, h1, // top right
};
std::copy(vertices, vertices + 264, blockVerts);

int indices[36] = {
	  0,  1,  2,    0,  2,  3, // top
	  6,  5,  4,    7,  6,  4, // bottom
	  8,  9, 10,    8, 10, 11, // left
	 12, 13, 14,   12, 14, 15, // front
	 18, 17, 16,   19, 18, 16, // right
	 22, 21, 20,   23, 22, 20, // behind
};
std::copy(indices, indices + 36, blockIndis);
#endif
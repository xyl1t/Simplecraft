#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <map>
#include <cstdint>
#include <string>

#define BLOCKS_AMOUNT		9
#define AIR_BLOCK			0
#define GRASS_BLOCK			1
#define DIRT_BLOCK			2
#define COBBLESTONE_BLOCK	3
#define SAND_BLOCK			4
#define WATER_BLOCK			5
#define STONE_BLOCK			6
#define PLANK_BLOCK			7
#define GLOWSTONE_BLOCK		8

// Assets is a singleton class
class Assets {
private:
	Assets();
	~Assets();

	int textureWidth, textureHeight;
	std::map<std::string, uint8_t*> textures;
	uint8_t* blockTextures[BLOCKS_AMOUNT];

	float blockVerts[264];
	int blockIndis[36];

public:
	inline static Assets& GetInstance() {
		static Assets me;
		
		return me;
	}

	void LoadAssets();
	void UnloadAssets();

	inline uint8_t* GetTexture(const std::string& name) {
		return textures[name];
	}
	inline uint8_t* GetTexture(size_t id) {
		return blockTextures[id];
	}
	inline int GetTextureWidth() {
		return textureWidth;
	}
	inline int GetTextureHeight() {
		return textureHeight;
	}

	inline float* GetBlockVertices() {
		return blockVerts;
	}
	inline size_t GetBlockVerticesSize() {
		return sizeof(blockVerts);
	}
	inline int* GetBlockIndices() {
		return blockIndis;
	}
	inline size_t GetBlockIndicesSize() {
		return sizeof(blockIndis);
	}
	
	Assets(const Assets& other) = delete;
	void operator=(const Assets& other) = delete;
};

#endif
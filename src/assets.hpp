#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <map>
#include <cstdint>
#include <string>
#include <glm/glm.hpp>

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

#define FACES_AMOUNT 6
#define FACE0	0
#define FACE1	1
#define FACE2	2
#define FACE3	3
#define FACE4	4
#define FACE5	5

// Assets is a singleton class
class Assets {
private:
	Assets();
	~Assets();

	int textureWidth, textureHeight;
	std::map<std::string, uint8_t*> textures;
	uint8_t* blockTextures[BLOCKS_AMOUNT];
	uint8_t* atlasTexture;
	int atlasWidth;
	int atlasHeight;
	int atlasTileWidth;
	int atlasTileHeight;
	int atlasNrChannels;

	glm::vec2 blockFacePositions[BLOCKS_AMOUNT][FACES_AMOUNT][4];

	float blockVerts[168];
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
	inline float GetNormalizedSpriteX(int x) {
		float val = x / (float)atlasTileWidth;
		return x / (float)atlasTileWidth;
	}
	inline float GetNormalizedSpriteY(int y) {
		return y / (float)atlasTileHeight;
	}
	inline uint8_t* GetAtlas() {
		return atlasTexture;
	}
	inline int GetAtlasWidth() {
		return atlasWidth;
	}
	inline int GetAtlasHeight() {
		return atlasHeight;
	}
	inline glm::vec2 GetTexturePosition(int blockType, int face, int vertex) {
		return blockFacePositions[blockType][face][vertex];
	}

	Assets(const Assets& other) = delete;
	void operator=(const Assets& other) = delete;
};

#endif
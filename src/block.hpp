#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <cstdint>


class Block {
private:

	uint8_t* texture;
	uint32_t x, y, z;
	uint8_t id;

public:
	Block();
	Block(uint8_t blockID, uint32_t x, uint32_t y, uint32_t z);
	~Block();

	inline uint8_t GetID() {
		return id;
	}
	
	void Update();
	void Draw();

	//void Move(uint32_t newX, uint32_t newY, uint32_t newZ);

	
};

#endif

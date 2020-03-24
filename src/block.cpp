#include "block.hpp"
#include "game.hpp"

Block::Block(): texture(nullptr) {
	x = 0;
	y = 0;
	z = 0;
	id = 0;
}
Block::~Block() {
}

Block::Block(uint8_t blockID, uint32_t x, uint32_t y, uint32_t z) {
	this->id = blockID;
	this->texture = Game::assets.GetTexture(id);

	this->x = x;
	this->y = y;
	this->z = z;
}

void Block::Update() {

}
void Block::Draw() {
	// if texture is 'nullptr' don't draw!
	if (texture == nullptr) return;

}

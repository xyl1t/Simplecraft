#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTextureCoords;
layout (location = 4) in float aID;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool neighbors[27];

uniform bool settingsAO;
uniform float AOintensity;

out vec3 normal;
out vec3 color;
out vec2 textureCoords;

int calcIndex(int x, int y, int z) {
	return x + y * 3 + z * 9;
}

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
	
	normal = aNormal;
	color = aColor;
	textureCoords = aTextureCoords;

	int x = 2;
	int y = 2;
	int z = 2;
	int index = calcIndex(x, y, z);

	if(!settingsAO) return;


	bool top = false, bottom = false, left = false, right = false;

	// top
	if (aNormal.y > 0) {

		if(neighbors[calcIndex(0, 2, 1)]) { // left
			if(aID == 1 || aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			left = true;
		}
		if(neighbors[calcIndex(2, 2, 1)]) { // right
			if(aID == 2 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			right = true;
		}
		if(neighbors[calcIndex(1, 2, 0)]) { // top
			if(aID == 0 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			top = true;
		}
		if(neighbors[calcIndex(1, 2, 2)]) { // bottom
			if(aID == 1 || aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			bottom = true;
		}
		
		if(neighbors[calcIndex(0, 2, 0)] && !top && !left) { // top left
			if(aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 2 && !neighbors[calcIndex(0, 2, 2)] && !neighbors[calcIndex(2, 2, 2)] && !neighbors[calcIndex(2, 2, 0)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(0, 2, 2)] && !bottom && !left) { // bottom left
			if(aID == 1) {
				color.r = color.b = color.g -= color.r * AOintensity;
			} 
			if(aID == 3  && !neighbors[calcIndex(0, 2, 0)] && !neighbors[calcIndex(2, 2, 2)] && !neighbors[calcIndex(2, 2, 0)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(2, 2, 2)] && !bottom && !right) { // bottom right
			if(aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 0 && !neighbors[calcIndex(0, 2, 0)] && !neighbors[calcIndex(2, 2, 0)] && !neighbors[calcIndex(0, 2, 0)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(2, 2, 0)] && !top && !right) { // top right
			if(aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 1 && !neighbors[calcIndex(0, 2, 0)] && !neighbors[calcIndex(0, 2, 2)] && !neighbors[calcIndex(2, 2, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}		
		}
	}

	top = bottom = left = right = false;

	// bottom
	if(aNormal.y < 0) {		
		if(neighbors[calcIndex(0, 0, 1)]) { // left
			if(aID == 1 || aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			left = true;
		}
		if(neighbors[calcIndex(2, 0, 1)]) { // right
			if(aID == 2 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			right = true;
		}
		if(neighbors[calcIndex(1, 0, 0)]) { // top
			if(aID == 0 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			top = true;
		}
		if(neighbors[calcIndex(1, 0, 2)]) { // bottom
			if(aID == 1 || aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			bottom = true;
		}
		
		if(neighbors[calcIndex(0, 0, 0)] && !top && !left) { // top left
			if(aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 2 && !neighbors[calcIndex(0, 0, 2)] && !neighbors[calcIndex(2, 0, 2)] && !neighbors[calcIndex(2, 0, 0)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(0, 0, 2)] && !bottom && !left) { // bottom left
			if(aID == 1) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 32 && !neighbors[calcIndex(0, 0, 0)] && !neighbors[calcIndex(2, 0, 2)] && !neighbors[calcIndex(2, 0, 0)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(2, 0, 2)] && !bottom && !right) { // bottom right
			if(aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 02 && !neighbors[calcIndex(0, 0, 0)] && !neighbors[calcIndex(0, 0, 2)] && !neighbors[calcIndex(2, 0, 0)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(2, 0, 0)] && !top && !right) { // top right
			if(aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 12 && !neighbors[calcIndex(0, 0, 0)] && !neighbors[calcIndex(0, 0, 2)] && !neighbors[calcIndex(2, 0, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
	}
	
	top = bottom = left = right = false;

	// left
	if(aNormal.x < 0) {		
		if(neighbors[calcIndex(0, 1, 0)]) { // left
			if(aID == 1 || aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			left = true;
		}
		if(neighbors[calcIndex(0, 1, 2)]) { // right
			if(aID == 2 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			right = true;
		}
		if(neighbors[calcIndex(0, 2, 1)]) { // top
			if(aID == 0 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			top = true;
		}
		if(neighbors[calcIndex(0, 0, 1)]) { // bottom
			if(aID == 1 || aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			bottom = true;
		}
		
		if(neighbors[calcIndex(0, 2, 0)] && !top && !left) { // top left
			if(aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 2 && !neighbors[calcIndex(0, 0, 0)] && !neighbors[calcIndex(0, 0, 2)] && !neighbors[calcIndex(0, 2, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(0, 0, 0)] && !bottom && !left) { // bottom left
			if(aID == 1) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 3 && !neighbors[calcIndex(0, 2, 0)] && !neighbors[calcIndex(0, 0, 2)] && !neighbors[calcIndex(0, 2, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(0, 0, 2)] && !bottom && !right) { // bottom right
			if(aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 0 && !neighbors[calcIndex(0, 2, 0)] && !neighbors[calcIndex(0, 0, 0)] && !neighbors[calcIndex(0, 2, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(0, 2, 2)] && !top && !right) { // top right
			if(aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 1 && !neighbors[calcIndex(0, 2, 0)] && !neighbors[calcIndex(0, 0, 0)] && !neighbors[calcIndex(0, 0, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
	}
	
	top = bottom = left = right = false;

	// right
	if(aNormal.x > 0) {		
		if(neighbors[calcIndex(2, 1, 0)]) { // left
			if(aID == 1 || aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			left = true;
		}
		if(neighbors[calcIndex(2, 1, 2)]) { // right
			if(aID == 2 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			right = true;
		}
		if(neighbors[calcIndex(2, 2, 1)]) { // top
			if(aID == 0 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			top = true;
		}
		if(neighbors[calcIndex(2, 0, 1)]) { // bottom
			if(aID == 1 || aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			bottom = true;
		}
		
		if(neighbors[calcIndex(2, 2, 0)] && !top && !left) { // top left
			if(aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 2 && !neighbors[calcIndex(2, 0, 0)] && !neighbors[calcIndex(2, 0, 2)] && !neighbors[calcIndex(2, 2, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(2, 0, 0)] && !bottom && !left) { // bottom left
			if(aID == 1) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 3  && !neighbors[calcIndex(2, 2, 0)] && !neighbors[calcIndex(2, 0, 2)] && !neighbors[calcIndex(2, 2, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(2, 0, 2)] && !bottom && !right) { // bottom right
			if(aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 0 && !neighbors[calcIndex(2, 2, 0)] && !neighbors[calcIndex(2, 0, 0)] && !neighbors[calcIndex(2, 2, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(2, 2, 2)] && !top && !right) { // top right
			if(aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 1 && !neighbors[calcIndex(2, 2, 0)] && !neighbors[calcIndex(2, 0, 0)] && !neighbors[calcIndex(2, 0, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
	}
	
	top = bottom = left = right = false;

	// front
	if(aNormal.z > 0) {
		if(neighbors[calcIndex(0, 1, 2)]) { // left
			if(aID == 1 || aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			left = true;
		}
		if(neighbors[calcIndex(2, 1, 2)]) { // right
			if(aID == 2 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			right = true;
		}
		if(neighbors[calcIndex(1, 2, 2)]) { // top
			if(aID == 0 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			top = true;
		}
		if(neighbors[calcIndex(1, 0, 2)]) { // bottom
			if(aID == 1 || aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			bottom = true;
		}
		
		if(neighbors[calcIndex(0, 2, 2)] && !top && !left) { // top left
			if(aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 2 && !neighbors[calcIndex(0, 0, 2)] && !neighbors[calcIndex(2, 0, 2)] && !neighbors[calcIndex(2, 2, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(0, 0, 2)] && !bottom && !left) { // bottom left
			if(aID == 1) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 3 && !neighbors[calcIndex(0, 2, 2)] && !neighbors[calcIndex(2, 0, 2)] && !neighbors[calcIndex(2, 2, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(2, 0, 2)] && !bottom && !right) { // bottom right
			if(aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 0 && !neighbors[calcIndex(0, 2, 2)] && !neighbors[calcIndex(0, 0, 2)] && !neighbors[calcIndex(2, 2, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(2, 2, 2)] && !top && !right) { // top right
			if(aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 1 && !neighbors[calcIndex(0, 2, 2)] && !neighbors[calcIndex(0, 0, 2)] && !neighbors[calcIndex(2, 0, 2)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
	}

	top = bottom = left = right = false;
	
	// behind
	if(aNormal.z < 0) {
		if(neighbors[calcIndex(0, 1, 0)]) { // left
			if(aID == 1 || aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			left = true;
		}
		if(neighbors[calcIndex(2, 1, 0)]) { // right
			if(aID == 2 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			right = true;
		}
		if(neighbors[calcIndex(1, 2, 0)]) { // top
			if(aID == 0 || aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			top = true;
		}
		if(neighbors[calcIndex(1, 0, 0)]) { // bottom
			if(aID == 1 || aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			bottom = true;
		}
		
		if(neighbors[calcIndex(0, 2, 0)] && !top && !left) { // top left
			if(aID == 0) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 2 && !neighbors[calcIndex(0, 0, 0)] && !neighbors[calcIndex(2, 0, 0)] && !neighbors[calcIndex(2, 2, 0)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(0, 0, 0)] && !bottom && !left) { // bottom left
			if(aID == 1) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 3 && !neighbors[calcIndex(0, 2, 0)] && !neighbors[calcIndex(2, 0, 0)] && !neighbors[calcIndex(2, 2, 0)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(2, 0, 0)] && !bottom && !right) { // bottom right
			if(aID == 2) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 0 && !neighbors[calcIndex(0, 2, 0)] && !neighbors[calcIndex(0, 0, 0)] && !neighbors[calcIndex(2, 2, 0)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
		if(neighbors[calcIndex(2, 2, 0)] && !top && !right) { // top right
			if(aID == 3) {
				color.r = color.b = color.g -= color.r * AOintensity;
			}
			if(aID == 1 && !neighbors[calcIndex(0, 2, 0)] && !neighbors[calcIndex(0, 0, 0)] && !neighbors[calcIndex(2, 0, 0)]) {
				color.r = color.b = color.g += color.r * AOintensity;
			}
		}
	}
}
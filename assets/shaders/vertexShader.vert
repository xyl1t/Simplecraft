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

	// top
	if (aNormal.y > 0) {
		if(neighbors[calcIndex(0, 2, 1)]) {
			if(aID == 1 || aID == 0) {
				color.r = color.b = color.g = 0.5f;
			}
		}
	}

	// bottom
	if(aNormal.y < 0) {
		
	}
	
	// left
	if(aNormal.x < 0) {
		
	}
	
	// front
	if(aNormal.z > 0) {
		
	}
	
	// right
	if(aNormal.x > 0) {
		
	}
	
	// behind
	if(aNormal.z < 0) {
		
	}

}
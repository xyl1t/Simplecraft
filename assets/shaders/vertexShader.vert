#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTextureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool neighbors[27];

out vec3 normal;
out vec3 color;
out vec2 textureCoords;


void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0f);

	normal = aNormal;
	color = aColor;
	textureCoords = aTextureCoords;

	int x = 2;
	int y = 2;
	int z = 2;
	int index = x + y * 3 + z * 9;

	if(neighbors[index]) {
		color = vec3(0.0f, 1.0f, 0.0f);
	}
}
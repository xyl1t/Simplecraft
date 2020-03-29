#version 330 core

in vec3 normal;
in vec3 color;
in vec2 textureCoords;

uniform sampler2D blockTexture;

out vec4 FragColor;

void main() {
	FragColor = texture(blockTexture, textureCoords);
	
	if(normal.x != 0)
		FragColor = texture(blockTexture, textureCoords) * 0.80f;
	if(normal.z != 0)
		FragColor = texture(blockTexture, textureCoords) * 0.70f;
	if(normal.y < 0)							    
		FragColor = texture(blockTexture, textureCoords) * 0.60f;

	FragColor *= color;
}
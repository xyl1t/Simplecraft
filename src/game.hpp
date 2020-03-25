#ifndef GAME_HPP
#define GAME_HPP

#include "block.hpp"
#include "assets.hpp"
#include "shader.hpp"
#include "camera.hpp"

#include <cstdint>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define SETTINGS_AO 0 
#define SETTINGS_SHADOW 1
#define SETTINGS_AO_INTENSITY 0


class Game {
private:

	void InitProgram();
	void InitGame();
	void FreeResources();

	void Update(float deltaTime);
	void ProccessInput(SDL_Event& windowEvent, float deltaTime);
	void Draw();

	const int WORLD_WIDTH;
	const int WORLD_HEIGHT;
	const int WORLD_DEPTH;
	Block*** world;
	//Block grass, dirt, cobblestone, sand, water, stone, plank, glowstone;
	
	bool alive;
	bool paused;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	SDL_Window* window;
	bool settings[2];
	float fSettings[1];

	SDL_GLContext glContext;
	Shader shader;
	uint32_t VAO, VBO, EBO;
	uint32_t textures[BLOCKS_AMOUNT];

	Camera camera;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	float fov;

public:
	Game(); // init

	static Assets& assets;

	void Run();
	void Pause();

	~Game(); // free resources
};

#endif
#include "game.hpp"
#include "block.hpp"

#include <glad/glad.h>
#include <iostream>

Assets& Game::assets = Assets::GetInstance();

Game::Game()
	: alive(false),
	WORLD_WIDTH(32),
	WORLD_HEIGHT(16),
	WORLD_DEPTH(32),
	WINDOW_WIDTH(800),
	WINDOW_HEIGHT(600),
	world{},
	VAO(0),
	VBO(0),
	EBO(0),
	camera(glm::vec3(0.0f, 17.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f),
	model{ glm::mat4(1.0f) },
	view{ glm::mat4(1.0f) },
	projection{ glm::mat4(1.0f) },
	fov(70.0f), 
	textures { } {
	camera.Position = glm::vec3(WORLD_WIDTH / 2, WORLD_HEIGHT / 2 + 2, WORLD_DEPTH / 2);
}
Game::~Game() {
	FreeResources();
}

void Game::InitProgram() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	window = SDL_CreateWindow("SimpleCraft", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(SDL_FALSE);

	//SDL_GL_SetSwapInterval(0);
	
	glContext = SDL_GL_CreateContext(window);

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
	}
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
}
void Game::InitGame() {
	// load assets
	Game::assets.LoadAssets();

	// Allocate memory for world
	world = new Block * *[WORLD_WIDTH];
	for (int i = 0; i < WORLD_WIDTH; i++) {
		world[i] = new Block * [WORLD_HEIGHT];
		for (int j = 0; j < WORLD_HEIGHT; j++) {
			world[i][j] = new Block[WORLD_DEPTH];
		}
	}

	
	// Fill world with data
	for (int x = 0; x < WORLD_WIDTH; x++) {
		for (int y = 0; y < WORLD_HEIGHT; y++) {
			for (int z = 0; z < WORLD_DEPTH; z++) {
				// First initialize with air
				world[x][y][z] = Block(AIR_BLOCK, x, y, z);

				// Fill bottom half of world with grass blocks
				if (y == WORLD_HEIGHT / 2) {
					if(rand()%4)
						world[x][y][z] = Block(GRASS_BLOCK, x, y, z);
				}
				if (y < WORLD_HEIGHT / 2) {
					if (rand() % 100 > 75)
						world[x][y][z] = Block(DIRT_BLOCK, x, y, z);
				}
				if (y < WORLD_HEIGHT / 2-1) {
					if (rand() % 100 > 35)
						world[x][y][z] = Block(COBBLESTONE_BLOCK, x, y, z);
				}
			}
		}
	}
	//world[WORLD_WIDTH / 2][WORLD_HEIGHT / 2+3][WORLD_DEPTH / 2] = Block(GLOWSTONE_BLOCK, 0,0,0);
	
	world[WORLD_WIDTH / 2][WORLD_HEIGHT / 2 + 3][WORLD_DEPTH / 2] = Block(SAND_BLOCK, 0, 0, 0);
	world[WORLD_WIDTH / 2][WORLD_HEIGHT / 2 + 3][WORLD_DEPTH / 2 - 1] = Block(SAND_BLOCK, 0, 0, 0);
	world[WORLD_WIDTH / 2][WORLD_HEIGHT / 2 + 3][WORLD_DEPTH / 2 + 1] = Block(SAND_BLOCK, 0, 0, 0);
	world[WORLD_WIDTH / 2 - 1][WORLD_HEIGHT / 2 + 3][WORLD_DEPTH / 2] = Block(SAND_BLOCK, 0, 0, 0);
	world[WORLD_WIDTH / 2 + 1][WORLD_HEIGHT / 2 + 3][WORLD_DEPTH / 2] = Block(SAND_BLOCK, 0, 0, 0);
	world[WORLD_WIDTH / 2][WORLD_HEIGHT / 2 + 3 - 1][WORLD_DEPTH / 2] = Block(SAND_BLOCK, 0, 0, 0);
	world[WORLD_WIDTH / 2][WORLD_HEIGHT / 2 + 3 + 1][WORLD_DEPTH / 2] = Block(SAND_BLOCK, 0, 0, 0);

	world[WORLD_WIDTH / 2][WORLD_HEIGHT / 2 + 1][WORLD_DEPTH / 2] = Block(SAND_BLOCK, 0, 0, 0);
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			world[WORLD_WIDTH / 2 + i][WORLD_HEIGHT / 2 + 1][WORLD_DEPTH / 2 + j] = Block(SAND_BLOCK, 0, 0, 0);
		}
	}


	// setup shader
	shader = Shader("assets/shaders/vertexShader.vert", "assets/shaders/fragmentShader.frag"); // TODO: get shader location from assets!
	shader.use();

	// setup projection matrix
	projection = glm::perspective(fov, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 500.f);
	shader.setMat4("projection", projection);


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, assets.GetBlockVerticesSize(), assets.GetBlockVertices(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, assets.GetBlockIndicesSize(), assets.GetBlockIndices(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(11 * sizeof(float)));
	glEnableVertexAttribArray(4);

	glGenTextures(BLOCKS_AMOUNT, textures);
	for (int i = 0; i < BLOCKS_AMOUNT; i++) {
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int w = assets.GetTextureWidth();
		int h = assets.GetTextureHeight();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, assets.GetTextureWidth(), assets.GetTextureHeight(), 0, 
			GL_RGBA, GL_UNSIGNED_BYTE, assets.GetTexture(i));
		glGenerateMipmap(GL_TEXTURE_2D);
	}

}


void Game::Run() {
	InitProgram();
	InitGame();
	
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	SDL_Event windowEvent;
	alive = true;
	while (alive) {
		float currentFrame = SDL_GetTicks()/1000.f;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProccessInput(windowEvent, deltaTime);

		Update(deltaTime);
		Draw();

		SDL_GL_SwapWindow(window);
	}
}
void Game::Pause() {
}

void Game::Update(float deltaTime) {
	for (int x = 0; x < WORLD_WIDTH; x++) {
		for (int y = 0; y < WORLD_HEIGHT; y++) {
			for (int z = 0; z < WORLD_DEPTH; z++) {
				world[x][y][z].Update();
			}
		}
	}

	view = glm::mat4(1.0f);
	view = glm::rotate(view, (float)M_PI / 8.f, glm::vec3(1.0f, 0.0f, 0.0f));	
	view = glm::translate(view, glm::vec3(0.0f, -24.0f, 0.0f));
	view = glm::rotate(view, (float)M_PI / 2.f, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, (float)M_PI / 4.f, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, (sin(SDL_GetTicks() / 1000.f) / 2.0f + 0.5f) * (float)M_PI/2.f - (float)M_PI/4.f, glm::vec3(0.0f, 1.0f, 0.0f));

	std::cout << "fps: " << 1.0f / deltaTime << "\n";
}
void Game::ProccessInput(SDL_Event& windowEvent, float deltaTime) {
	while (SDL_PollEvent(&windowEvent)) {
		switch (windowEvent.type) {
			case SDL_QUIT:
				alive = false;
				break;

			case SDL_MOUSEMOTION:

				camera.ProcessMouseMovement(windowEvent.motion.xrel, -windowEvent.motion.yrel, true);

				break;
		}
	}

	uint8_t* keyboard;
	SDL_PumpEvents();
	keyboard = (uint8_t*)SDL_GetKeyboardState(NULL);

	if (keyboard[SDL_SCANCODE_W]) {
		// cameraPos += cameraSpeed * vec3(cameraFront.x, 0.0f, cameraFront.z);
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	}
	if (keyboard[SDL_SCANCODE_S]) {
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	}
	if (keyboard[SDL_SCANCODE_A]) {
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	}
	if (keyboard[SDL_SCANCODE_D]) {
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	}
	if (keyboard[SDL_SCANCODE_SPACE]) {
		camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
	}
	if (keyboard[SDL_SCANCODE_LSHIFT]) {
		camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
	}
	if (keyboard[SDL_SCANCODE_LCTRL]) {
		camera.MovementSpeed = 7.5f;
	}
	else {
		camera.MovementSpeed = 3.0f;
	}
}
void Game::Draw() {

	shader.setMat4("view", camera.GetViewMatrix());

	glClearColor(0.5f, 0.75f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int x = 0; x < WORLD_WIDTH - 0; x++) {
		for (int y = 0; y < WORLD_HEIGHT - 0; y++) {
			for (int z = 0; z < WORLD_DEPTH - 0; z++) {
				Block& current = world[x][y][z];
				// Skip if block is air
				if (current.GetID() == AIR_BLOCK) continue;

				int neighbors[27] = { };
				for (int lx = -1; lx < 2; lx++) {
					for (int ly = -1; ly < 2; ly++) {
						for (int lz = -1; lz < 2; lz++) {

							if (lx + x >= 0 &&
								ly + y >= 0 &&
								lz + z >= 0 &&
								lx + x < WORLD_WIDTH &&
								ly + y < WORLD_HEIGHT &&
								lz + z < WORLD_DEPTH) {

								if (lx == 0 && ly == 0 && lz == 0) continue;								

								neighbors[(lx + 1) + (ly + 1) * 3 + (lz + 1) * 9] = world[lx + x][ly + y][lz + z].GetID() != AIR_BLOCK;
							}
							else {
								neighbors[(lx + 1) + (ly + 1) * 3 + (lz + 1) * 9] = false;
							}
						}
					}
				}

				// Skip if surrounded by other blocks
				if ((x - 1 >= 0				&& world[x - 1][y][z].GetID() != AIR_BLOCK) &&
					(y - 1 >= 0				&& world[x][y - 1][z].GetID() != AIR_BLOCK) &&
					(z - 1 >= 0				&& world[x][y][z - 1].GetID() != AIR_BLOCK) &&
					(x + 1 < WORLD_WIDTH	&& world[x + 1][y][z].GetID() != AIR_BLOCK) &&
					(y + 1 < WORLD_HEIGHT	&& world[x][y + 1][z].GetID() != AIR_BLOCK) &&
					(z + 1 < WORLD_DEPTH	&& world[x][y][z + 1].GetID() != AIR_BLOCK)) continue;
				
				// position the block in the world
				model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
				shader.setMat4("model", model);

				// bind the corresponding texture
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textures[current.GetID()]);

				glUniform1iv(glGetUniformLocation(shader.ID, "neighbors"), 27, neighbors);

				// draw the block
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
				//glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}
	}
}


void Game::FreeResources() {
	// Deallocate world
	for (int i = 0; i < WORLD_WIDTH; i++) {
		for (int j = 0; j < WORLD_HEIGHT; j++) {
			delete[] world[i][j];
		}
		delete[] world[i];
	}
	delete[] world;

	// Unload assets (textures)
	assets.UnloadAssets();
}

#if 0

#endif
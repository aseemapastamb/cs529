/*  Start Header -

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is
prohibited.

File Name: main.cpp
Purpose: Implementation of game - SDL, Game Loop, Input
Language: C++
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS529_aseemapastamb_milestone_1
Author: Aseem Apastamb, aseem.apastamb, 60000620
Creation date: 11/16/2021

- End Header
----------------------------------------------------------------------- */
#include "Windows.h"
#include <SDL.h>
#include "stdio.h"
#include <glad/glad.h>
#include <ctime>

#include "Component.h"
#include "Sprite.h"
#include "Transform.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Shader.h"
#include "Renderer.h"
#include "FrameRateController.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "EventManager.h"
#include "CollisionManager.h"
#include "GameStateManager.h"

using namespace std;

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

FrameRateController* gpFrameRateController = nullptr;
InputManager* gpInputManager = nullptr;
ResourceManager* gpResourceManager = nullptr;
GameObjectManager* gpGameObjectManager = nullptr;
GameObjectFactory* gpGameObjectFactory = nullptr;
EventManager* gpEventManager = nullptr;
CollisionManager* gpCollisionManager = nullptr;
GameStateManager* gpGameStateManager = nullptr;
Renderer* gpRenderer = nullptr;

SDL_Window* gpWindow = nullptr;

int width = 800;
int height = 600;

bool appIsRunning = NULL;

int main(int argc, char* args[])
{
	srand(static_cast <unsigned> (time(0)));

	if (AllocConsole())
	{
		FILE* file;
		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);
		SetConsoleTitle(L"Game Engine Debug Console");
	}

	cout << "Console created." << endl;

	int error = 0;
	appIsRunning = true;

	// Define globals
	gpGameStateManager = new GameStateManager();
	gpFrameRateController = new FrameRateController(60);
	gpInputManager = new InputManager();
	gpResourceManager = new ResourceManager();
	gpGameObjectManager = new GameObjectManager();
	gpGameObjectFactory = new GameObjectFactory();
	gpEventManager = new EventManager();
	gpCollisionManager = new CollisionManager();
	gpRenderer = new Renderer();

	// Initialize SDL
	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}

	gpWindow = SDL_CreateWindow("SDL2 window",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		width,										// width, in pixels
		height,										// height, in pixels
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	// Check that the window was successfully made
	if (NULL == gpWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(gpWindow);
	SDL_GL_MakeCurrent(gpWindow, glContext);

	// Loading OpenGL through glad
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return 1;
	}

	// Load level
	gpGameStateManager->Initialize("level0.json");
	gpGameStateManager->Update();

	gpRenderer->Initialize();

	// Game loop
	while (true == appIsRunning)
	{
		// Set start time
		gpFrameRateController->frameStartTime();

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				appIsRunning = false;
			}
		}

		gpInputManager->Update();

		gpCollisionManager->Update();

		gpEventManager->Update(gpFrameRateController->getDeltaTime());

		gpGameStateManager->Update();

		gpGameObjectManager->Update();

		gpRenderer->Draw();

		gpGameObjectManager->RemoveDestroyed();

		if (gpInputManager->isKeyTriggered(SDL_SCANCODE_ESCAPE)) {
			appIsRunning = false;
		}

		gpFrameRateController->frameEndTime();
		//SDL_Log("frame time = %u", gpFrameRateController->getFrameTime());
	}

	// delete Renderer
	delete gpRenderer;

	delete gpEventManager;
	delete gpCollisionManager;

	// Destroy Frame Rate Controller
	delete gpFrameRateController;

	// Destroy Input Manager
	delete gpInputManager;

	// Destroy Resource Manager
	delete gpResourceManager;

	// Destroy Game Object Manager
	delete gpGameObjectManager;

	// Destroy Game Object Factory
	delete gpGameObjectFactory;

	delete gpGameStateManager;

	// Delete OpenGL context
	SDL_GL_DeleteContext(glContext);

	// Close and destroy the window
	SDL_DestroyWindow(gpWindow);

	// Quit SDL subsystems
	SDL_Quit();

	FreeConsole();

	return 0;
}
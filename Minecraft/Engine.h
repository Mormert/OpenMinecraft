#pragma once

#include "Window.h"
#include "Renderer.h"
#include "ImGuiRenderer.h"
#include "Camera.h"
#include "Game.h"

class Engine
{
public:
	Engine();
	void Run();

    static inline Engine* engine;

private:

    // Used for Emscripten...
    static void main_loop()
    {
        Engine::engine->MainLoop();
    }

	void Loop();
    void MainLoop();

	void CollectInput();
	void Update();

	bool running{ false };

	Window window;
	Renderer renderer;
	ImGuiRenderer imGuiRenderer;
	Camera camera;
	Game game;
};



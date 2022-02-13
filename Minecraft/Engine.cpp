#include "Engine.h"

#include "EngineStatus.h"

#include "BlockLoader.h"
#include "KeyboardEvents.h"
#include "InputManager.h"

#include <GLFW/glfw3.h>

#include <iostream>

const char*		WINDOW_TITLE	{ "Minecraft" };
constexpr int	SCR_WIDTH		{ 1920 };
constexpr int	SCR_HEIGHT		{ 1080 };

Engine::Engine() :
	window			{ SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE },
	renderer		{ SCR_WIDTH, SCR_HEIGHT, camera },
	imGuiRenderer	{ &window.GetNativeWindow() },
	game			{ renderer.GetBlockRenderer() }
{

	window.SetResizeWindowEvent(InputManager::ResizeWindowEvent);
	window.SetKeyPressedEvent(InputManager::KeyPressedEvent);
	window.SetKeyReleasedEvent(InputManager::KeyReleasedEvent);
	window.FpsModeCursor(true);
	window.SetMainWindow();

	InputManager::AddResizeWindowCallback(&renderer, &Renderer::SetAspectRatio);
	InputManager::LinkWindow(&window);

	camera.SetMainCamera();
}

void Engine::Run()
{
	running = true;

    engine = this;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, true);
#else
    Loop();
#endif


}

void Engine::Loop()
{
	while (running)
	{
        MainLoop();
	}
}

void Engine::CollectInput()
{
	InputManager::FlushKeyPresses();
	InputManager::UpdateLastMousePosition();
	window.PollEvents();
}

void Engine::Update()
{
	KeyboardEvents::ProcessKeyboardEvents();
	game.Update(EngineStatus::deltaTime);
}

void Engine::MainLoop() {

    EngineStatus::currentFrame = glfwGetTime();
    EngineStatus::deltaTime = EngineStatus::currentFrame - EngineStatus::lastFrame;
    EngineStatus::lastFrame = EngineStatus::currentFrame;
    EngineStatus::fps = static_cast<int>(1.0 / EngineStatus::deltaTime);

    Update();

    renderer.Render();
    imGuiRenderer.Render();

    CollectInput();

    window.SwapBuffers();

    running = !window.ShouldClose();
}

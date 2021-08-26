#include "Engine.h"

#include "EngineStatus.h"

#include "BlockLoader.h"
#include "KeyboardEvents.h"
#include "InputManager.h"

#include <GLFW/glfw3.h>

#include <iostream>

const char*		WINDOW_TITLE	{ "Minecraft" };
constexpr int	SCR_WIDTH		{ 1200 };
constexpr int	SCR_HEIGHT		{ 1000 };

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
	
	std::cout << "tjoo \n heyyy \n looool";

	running = true;
	Loop();
}

void Engine::Loop()
{
	while (running)
	{

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
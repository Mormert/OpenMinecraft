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
constexpr float CAM_FOV			{ 45.0f };

Engine::Engine()
{
	window = new Window(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE);
	window->SetResizeWindowEvent(InputManager::ResizeWindowEvent);
	window->SetKeyPressedEvent(InputManager::KeyPressedEvent);
	window->SetKeyReleasedEvent(InputManager::KeyReleasedEvent);
	
	window->FpsModeCursor(true);
	window->SetMainWindow();

	BlockLoader::LoadBlocksFromFile("blockdata.txt");

	renderer = new Renderer(SCR_WIDTH, SCR_HEIGHT, CAM_FOV);

	InputManager::AddResizeWindowCallback(renderer, &Renderer::SetAspectRatio);
	InputManager::LinkWindow(window);

	imGuiRenderer = new ImGuiRenderer(&window->GetNativeWindow());

	camera = new Camera();
	camera->SetMainCamera();
}

Engine::~Engine()
{
	delete imGuiRenderer;
	delete renderer;
	delete window;
	delete camera;
}

void Engine::Run()
{
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

		renderer->Render(*camera);
		imGuiRenderer->Render();

		CollectInput();

		window->SwapBuffers();
		
		running = !window->ShouldClose();
	}
}

void Engine::CollectInput()
{
	InputManager::FlushKeyPresses();
	InputManager::UpdateLastMousePosition();
	window->PollEvents();
}

void Engine::Update()
{
	KeyboardEvents::ProcessKeyboardEvents();

}
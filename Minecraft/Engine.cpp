#include "Engine.h"

#include "InputManager.h"
#include "CameraController.h"

#include <GLFW/glfw3.h>

#include <iostream>

int EngineStatus::fps{ 0 };
float EngineStatus::deltaTime{ 0.0f };
float EngineStatus::currentFrame{ 0.0f };
float EngineStatus::lastFrame{ 0.0f };
double EngineStatus::time{ 0.0 };

const char*		WINDOW_TITLE	{ "Minecraft" };
constexpr int	SCR_WIDTH		{ 1200 };
constexpr int	SCR_HEIGHT		{ 1000 };
constexpr float CAM_FOV			{ 45.0f };

Engine::Engine()
{
	renderWindow = new Window(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE, InputManager::ResizeWindowEvent);
	renderWindow->FpsModeCursor(false);

	renderer = new Renderer(SCR_WIDTH, SCR_HEIGHT, CAM_FOV);

	InputManager::AddResizeWindowCallback(renderer, &Renderer::SetAspectRatio);
	InputManager::LinkWindow(renderWindow);

	imGuiRenderer = new ImGuiRenderer(&renderWindow->GetNativeWindow());

	camera = new Camera();
}

Engine::~Engine()
{
	delete imGuiRenderer;
	delete renderer;
	delete renderWindow;
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

		Update(EngineStatus::deltaTime);

		renderer->Render(*camera);
		imGuiRenderer->Render();

		CollectInput();

		renderWindow->SwapBuffers();
		
		running = !renderWindow->ShouldClose();
	}
}

void Engine::CollectInput()
{
	InputManager::FlushKeyPressArray();
	InputManager::UpdateLastMousePosition();
	renderWindow->PollEvents();
}

void Engine::Update(float dt)
{
	CameraController::MoveCameraBasedOnInput(*camera, dt);

	
}
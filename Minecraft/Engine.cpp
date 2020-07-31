#include "Engine.h"


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "InputManager.h"
#include "CameraController.h"

#include <GLFW/glfw3.h>

#include <iostream>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void Engine::Start()
{
	renderer = new Renderer();
	renderWindow = new Window(1200, 1000, "Minecraft", InputManager::ResizeWindowEvent);

	InputManager::AddResizeWindowCallback(renderer, &Renderer::SetAspectRatio);

	renderWindow->FpsModeCursor(false);

	InputManager::LinkWindow(renderWindow);

	imGuiRenderer = new ImGuiRenderer(&renderWindow->GetNativeWindow());

	camera = new Camera();
	renderer->Init(1200, 1000, 45.0f);

	gameManager = new GameManager();
	gameManager->GameInit();
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
		
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		Update(deltaTime);
		Render();

		imGuiRenderer->Render();

		CollectInput();

		renderWindow->SwapBuffers();
		
		running = !renderWindow->ShouldClose();
	}
	Close();
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

void Engine::Render()
{
	renderer->Render(*camera);
}

void Engine::Stop()
{
	running = false;
}

void Engine::Close()
{
	delete imGuiRenderer;
	delete renderWindow;
	delete renderer;
	delete camera;
}
#pragma once

#include "Window.h"
#include "Renderer.h"
#include "ImGuiRenderer.h"
#include "Camera.h"
#include "GameManager.h"

class Engine
{
public:
	void Start();
	void Run();
private:

	void Loop();

	void CollectInput();
	void Update(float dt);
	void Render();

	bool running{ false };
	void Stop();
	void Close();

	Window* renderWindow;
	Renderer* renderer;
	ImGuiRenderer* imGuiRenderer;
	Camera* camera;
	GameManager* gameManager;
};
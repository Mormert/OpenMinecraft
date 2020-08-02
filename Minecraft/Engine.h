#pragma once

#include "Window.h"
#include "Renderer.h"
#include "ImGuiRenderer.h"
#include "Camera.h"
#include "GameManager.h"

class Engine
{
public:
	Engine();
	~Engine();
	void Run();
	
private:

	void Loop();

	void CollectInput();
	void Update();

	bool running{ false };

	Window* renderWindow;
	Renderer* renderer;
	ImGuiRenderer* imGuiRenderer;
	Camera* camera;
};
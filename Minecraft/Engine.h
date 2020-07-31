#pragma once

#include "Window.h"
#include "Renderer.h"
#include "ImGuiRenderer.h"
#include "Camera.h"
#include "GameManager.h"

class EngineStatus
{
public:
	static int GetFps();
	static float GetDeltaTime();
	static double GetTime();

private:
	static int fps;
	static float deltaTime;
	static float currentFrame;
	static float lastFrame;
	static double time;

	friend class Engine;
};

class Engine
{
public:
	Engine();
	~Engine();
	void Run();
	
private:

	void Loop();

	void CollectInput();
	void Update(float dt);

	bool running{ false };

	Window* renderWindow;
	Renderer* renderer;
	ImGuiRenderer* imGuiRenderer;
	Camera* camera;
};
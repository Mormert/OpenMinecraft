#include "InputManager.h"

#include <GLFW/glfw3.h>

#include <iostream>

bool InputManager::keyPressed[256];
int InputManager::mouseX{ 0 };
int InputManager::mouseY{ 0 };
int InputManager::lastX{ 0 };
int InputManager::lastY{ 0 };
float InputManager::scrollX{ 0.0f };
float InputManager::scrollY{ 0.0f };
Window* InputManager::window{ nullptr };
std::vector<std::function<void(int, int)>> InputManager::resizeWindowCallbacks{};

bool InputManager::GetKeyPressed(char key)
{
	return keyPressed[key];
}

bool InputManager::GetKeyDown(char key)
{
	return glfwGetKey(&window->GetNativeWindow(), key);
}


int InputManager::GetMouseX()
{
	double x, y;
	glfwGetCursorPos(&window->GetNativeWindow(), &x, &y);
	return static_cast<int>(x);
}

int InputManager::GetMouseY()
{
	double x, y;
	glfwGetCursorPos(&window->GetNativeWindow(), &x, &y);
	return static_cast<int>(y);
}

float InputManager::GetMouseXDelta()
{
	double x, y;
	glfwGetCursorPos(&window->GetNativeWindow(), &x, &y);
	return x - lastX;
}

float InputManager::GetMouseYDelta()
{
	double x, y;
	glfwGetCursorPos(&window->GetNativeWindow(), &x, &y);
	return lastY - y;
}

float InputManager::GetScrollX()
{
	return scrollX;
}

float InputManager::GetScrollY()
{
	return scrollY;
}

void InputManager::SetKeyPressed(char key)
{
	keyPressed[key] = true;
}


void InputManager::SetScrollX(float xscrl)
{
	scrollX = xscrl;
}

void InputManager::SetScrollY(float yscrl)
{
	scrollY = yscrl;
}

void InputManager::LinkWindow(Window *w)
{
	window = w;
}

void InputManager::ResizeWindowEvent(int x, int y)
{
	for (const auto& cb : resizeWindowCallbacks) { cb(x, y); }
}

void InputManager::UpdateLastMousePosition()
{
	double x, y;
	glfwGetCursorPos(&window->GetNativeWindow(), &x, &y);
	lastX = static_cast<int>(x);
	lastY = static_cast<int>(y);
}

void InputManager::FlushKeyPressArray()
{
	for (unsigned int i = 0; i < 256; i++)
	{
		keyPressed[i] = false;
	}
}
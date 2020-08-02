#pragma once

#include "Window.h"

#include <functional>
#include <vector>


class InputManager
{
public:

	// Was a key pressed?
	static bool GetKeyPressed(char key);

	// Is a key held down?
	static bool GetKeyDown(char key);

	static int GetMouseX();
	static int GetMouseY();

	static float GetMouseXDelta();
	static float GetMouseYDelta();

	static float GetScrollX();
	static float GetScrollY();

	// Link the input manager to a window
	static void LinkWindow(Window *w);

	// Called from window manager
	static void SetKeyPressed(char key);
	static void SetScrollX(float xscrl);
	static void SetScrollY(float yscrl);

	static void UpdateLastMousePosition();
	static void FlushKeyPressArray();

	static void ResizeWindowEvent(int x, int y);

	template<class T> static void AddResizeWindowCallback(T* const object, void(T::* const mf)(int, int))
	{
		using namespace std::placeholders;
		resizeWindowCallbacks.emplace_back(std::bind(mf, object, _1, _2));
	}

private:
	static bool keyPressed[];
	static bool keyDown[];
	static int mouseX, mouseY;
	static int lastX, lastY;
	static float scrollX, scrollY;
	static Window* window;
	static std::vector<std::function<void(int, int)>> resizeWindowCallbacks;
};


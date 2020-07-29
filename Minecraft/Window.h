#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height, const char* title, void (*resizeWindowEvent)(int,int) = nullptr);
	~Window();

	void PollEvents();
	void SwapBuffers();

	void FpsModeCursor(bool enabled);

	bool ShouldClose();

	GLFWwindow &GetNativeWindow();
private:
	GLFWwindow *glfwWindow;

	int window_width;
	int window_height;

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	static void(*resizeEvent)(int, int);
};
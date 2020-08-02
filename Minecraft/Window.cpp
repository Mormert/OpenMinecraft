#include "Window.h"

#include "InputManager.h"

#include <iostream>

void Window::error_callback(int error, const char* description)
{
	std::cerr << "GLFW ERROR: " << description << '\n';
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	InputManager::SetScrollX(static_cast<float>(xoffset));
	InputManager::SetScrollY(static_cast<float>(yoffset));
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	if (resizeEvent){ (*resizeEvent)(width, height); }
}

void (*Window::resizeEvent)(int,int) { nullptr };

Window::Window(int width, int height, const char* title, void(*resizeWindowEvent)(int, int))
	: window_width{ width }, window_height{ height }
{

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		std::cerr << "GLFW ERROR: COULD NOT INITIALIZE";
		exit(1);
	}

	// Runs on OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// To Enable MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (!glfwWindow)
	{
		glfwTerminate();
		std::cerr << "GLFW ERROR: COULD NOT CREATE WINDOW";
		exit(1);
	}

	glfwSetKeyCallback(glfwWindow, key_callback);
	glfwSetScrollCallback(glfwWindow, scroll_callback);
	glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
	resizeEvent = resizeWindowEvent;

	glfwMakeContextCurrent(glfwWindow);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "ERROR: Failed to initialize GLAD\n";
		exit(1);
	}

	glfwSwapInterval(0);

	int w, h;
	glfwGetFramebufferSize(glfwWindow, &w, &h);
	glViewport(0, 0, width, height);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(glfwWindow);
}

void Window::FpsModeCursor(bool enable)
{
	if (enable)
	{
		glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else
	{
		glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

Window::~Window()
{
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(glfwWindow);
}

GLFWwindow &Window::GetNativeWindow()
{
	return *glfwWindow;
}
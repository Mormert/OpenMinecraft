#include "ImGuiRenderer.h"


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "InputState.h"
#include "EngineStatus.h"

#include <iostream>

void RenderDebugInfo();

ImGuiRenderer::ImGuiRenderer(GLFWwindow *window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	// Setup Dear ImGui style
	ImGui::StyleColorsClassic();
}

ImGuiRenderer::~ImGuiRenderer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiRenderer::Render()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	

	if (InputState::state.showDebugInfo)
	{
		RenderDebugInfo();
	}
		

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void RenderDebugInfo()
{
	
	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoMove;
	if (ImGui::Begin("Debug info", nullptr, window_flags))
	{
		ImGui::Text("FPS   : %d", EngineStatus::GetFps());
		ImGui::Text("MS    : %f", EngineStatus::GetDeltaTime());
	}
	ImGui::End();
	
}
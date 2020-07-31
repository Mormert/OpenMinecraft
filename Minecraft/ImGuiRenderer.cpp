#include "ImGuiRenderer.h"


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

	ImGui::ShowDemoWindow();

	// render your GUI
	ImGui::Begin("Triangle Position/Color");
	static float rotation = 0.0;
	ImGui::SliderFloat("rotation", &rotation, 0, 2 * 3.141592653589);
	static float translation[] = { 0.0, 0.0 };
	ImGui::SliderFloat2("position", translation, -1.0, 1.0);
	static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
	// pass the parameters to the shader
	// color picker
	ImGui::ColorEdit3("color", color);
	// multiply triangle's color with this color
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



}
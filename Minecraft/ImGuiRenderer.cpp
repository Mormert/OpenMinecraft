#include "ImGuiRenderer.h"

#include "World.h"
#include "Camera.h"
#include "InputState.h"
#include "EngineStatus.h"

#include "3rdparty/ImGui/imgui.h"
#include "3rdparty/ImGui/imgui_impl_glfw.h"
#include "3rdparty/ImGui/imgui_impl_opengl3.h"

#include <iostream>

void RenderDebugInfo();

ImGuiRenderer::ImGuiRenderer(GLFWwindow *window)
{
    // Currently only support ImGui on desktop.

#ifdef __EMSCRIPTEN__
#else

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    // Setup Dear ImGui style
    ImGui::StyleColorsClassic();

#endif

}

ImGuiRenderer::~ImGuiRenderer()
{
    // Currently only support ImGui on desktop.

#ifdef __EMSCRIPTEN__
#else
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif
}

void ImGuiRenderer::Render()
{

    // Currently only support ImGui on desktop.

#ifdef __EMSCRIPTEN__
#else
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	

	if (InputState::state.showDebugInfo)
	{
		RenderDebugInfo();
	}
		

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}

void RenderDebugInfo()
{

    // Currently only support ImGui on desktop.

#ifdef __EMSCRIPTEN__
#else

	constexpr ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoMove;
	if (ImGui::Begin("Debug info", nullptr, window_flags))
	{
		ImGui::Text("FPS : %d (%f ms)", EngineStatus::GetFps(), EngineStatus::GetDeltaTime());
		ImGui::Text("Posf   : %f, %f, %f", Camera::GetMainCamera()->Position.x, Camera::GetMainCamera()->Position.y, Camera::GetMainCamera()->Position.z);
		ImGui::Text("Posi   : %d, %d, %d", Camera::GetMainCamera()->GetIntegerWorldPos().x, Camera::GetMainCamera()->GetIntegerWorldPos().y, Camera::GetMainCamera()->GetIntegerWorldPos().z);
		ImGui::Text("Last Pressed  : %c (%d)", InputState::debugState.lastPressedButton, InputState::debugState.lastPressedButton);
		ImGui::Text("Last Released : %c (%d)", InputState::debugState.lastReleasedButton, InputState::debugState.lastReleasedButton);
        auto pos = Camera::GetMainCamera()->GetIntegerWorldPosOffsetted(glm::vec3{0.5f, 0.5f, 0.5f});
        ImGui::Text("Block Type : %d", World::g_world->GetBlockAtWorldPosition(pos.x, pos.y, pos.z));
        ImGui::Text("ChunkX : %d, ChunkZ : %d", World::g_world->chunkX, World::g_world->chunkZ);
        ImGui::Text("localBlockX : %d, localBlockZ : %d", World::g_world->localBlockX, World::g_world->localBlockZ);
	}
	ImGui::End();
#endif
}
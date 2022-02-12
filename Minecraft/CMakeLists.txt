cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

project(OpenMinecraft)

add_executable(OpenMinecraft
        "3rdparty/ImGui/imgui.cpp"
        "3rdparty/ImGui/imgui_demo.cpp"
        "3rdparty/ImGui/imgui_draw.cpp"
        "3rdparty/ImGui/imgui_impl_glfw.cpp"
        "3rdparty/ImGui/imgui_impl_opengl3.cpp"
        "3rdparty/ImGui/imgui_widgets.cpp"
        "3rdparty/glad/glad.c"
        "BlockLoader.cpp"
        "BlockRenderer.cpp"
        "Camera.cpp"
        "Chunk.cpp"
        "Engine.cpp"
        "EngineStatus.cpp"
        "Game.cpp"
        "ImGuiRenderer.cpp"
        "InputManager.cpp"
        "InputState.cpp"
        "KeyboardEvents.cpp"
        "main.cpp"
        "Player.cpp"
        "Renderer.cpp"
        "Shader.cpp"
        "Skybox.cpp"
        "stb_image.cpp"
        "Window.cpp"
        "World.cpp"
        "WorldGenerator.cpp"
        "FastNoise/FastNoise.cpp"
        "stb_image.h"
        "PairHash.h")

# Remove GLFW tests, examples and docs from build
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(3rdparty/glfw)
target_link_libraries(OpenMinecraft PUBLIC glfw)

target_include_directories(OpenMinecraft SYSTEM PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty"
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glad"
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm")


FILE(COPY data DESTINATION ${PROJECT_BINARY_DIR})
cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

project(OpenMinecraft)

option(BUILD_EMSCRIPTEN "Build game for web browsers" OFF)

add_executable(OpenMinecraft
        "3rdparty/ImGui/imgui.cpp"
        "3rdparty/ImGui/imgui_demo.cpp"
        "3rdparty/ImGui/imgui_draw.cpp"
        "3rdparty/ImGui/imgui_impl_glfw.cpp"
        "3rdparty/ImGui/imgui_impl_opengl3.cpp"
        "3rdparty/ImGui/imgui_widgets.cpp"
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


if(BUILD_EMSCRIPTEN) # Build to Web...

    target_include_directories(OpenMinecraft SYSTEM PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm")

    # set .html here so that we get .html output file.
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o index.html -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 --shell-file ../shell_minimal.html --preload-file data")

else() # Non-Web Build...

    # Compile also glad.c
    target_sources(OpenMinecraft PRIVATE "3rdparty/glad/glad.c")

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
endif()




FILE(COPY data DESTINATION ${PROJECT_BINARY_DIR})
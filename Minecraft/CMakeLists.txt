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
        "Renderer.cpp"
        "Shader.cpp"
        "Skybox.cpp"
        "stb_image.cpp"
        "Window.cpp"
        "World.cpp"
        "WorldGenerator.cpp"
        "FastNoise/FastNoise.cpp"
        "PlayerRenderer.cpp"
        "Networking.cpp"
        "NetworkingNative.cpp"
        "NetworkingJS.cpp")

if (BUILD_EMSCRIPTEN) # Build to Web...

    target_include_directories(OpenMinecraft SYSTEM PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm")

    # set .html here so that we get .html output file.
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o index.html -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_RUNTIME_METHODS=cwrap,allocate,intArrayFromString -s EXPORTED_FUNCTIONS=_main,_resize_canvas_js,_position_event_js,_block_update_event_js,_socket_io_connected_js --shell-file ../shell_fullscreen.html --preload-file data")

    #add_definitions("-s EXPORTED_RUNTIME_METHODS='[\"ccall\",\"cwrap\"]'")
    #add_definitions("-s EXTRA_EXPORTED_RUNTIME_METHODS='[\"ccall\",\"cwrap\"]'")
    #add_definitions("-s EXPORTED_FUNCTIONS='[\"_resize_canvas_js\",\"_main\"]'")
    #set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-s EXPORTED_RUNTIME_METHODS =['ccall','cwrap']" "-s EXPORTED_FUNCTIONS=['_resize_canvas_js','_main']")

else () # Non-Web Build...

    add_subdirectory(3rdparty/socket.io-cpp)
    target_link_libraries(OpenMinecraft PUBLIC sioclient)
    target_include_directories(OpenMinecraft SYSTEM PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/socket.io-cpp/src")

    # Compile also glad.c when building w/o emscripten
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
endif ()


FILE(COPY data DESTINATION ${PROJECT_BINARY_DIR})
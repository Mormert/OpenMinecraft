cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

project(EnvSensor)

add_executable(EnvSensor
        "main.cpp")

add_subdirectory(3rdparty/cpp-httplib)
target_link_libraries(EnvSensor PUBLIC httplib)

target_include_directories(EnvSensor SYSTEM PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/cpp-httplib"
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/")
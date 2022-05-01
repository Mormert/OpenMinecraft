cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

project(EnvSensor)

add_executable(EnvSensor
        3rdparty/TSL2591X/TSL2591.cpp
        3rdparty/TSL2591X/Config/dev_hardware_i2c.cpp
        3rdparty/TSL2591X/Config/sysfs_gpio.cpp
        3rdparty/TSL2591X/Config/DEV_Config.cpp
        "main.cpp")

# Set to USE_DEV_LIB, or USE_BCM2835_LIB or USE_WIRINGPI_LIB
# Depending on what library to use. DEV_LIB has no dependencies.
add_compile_definitions(USE_DEV_LIB)

add_subdirectory(3rdparty/cpp-httplib)
target_link_libraries(EnvSensor PUBLIC httplib)

target_include_directories(EnvSensor SYSTEM PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/cpp-httplib"
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/TSL2591X"
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/TSL2591X/Config"
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/")
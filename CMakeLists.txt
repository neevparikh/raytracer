cmake_minimum_required(VERSION 3.15)

# set the project name
project(raytracer)

set(SOURCES 
    ./src/main.cpp
    ./src/raytracer.cpp
    ./src/colors.cpp
    ./src/geometery.cpp
    ./src/camera.cpp
    ./src/scene.cpp
)

include_directories(./include)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# add the executable
add_executable(raytracer ${SOURCES})

# Eigen as a linear algebra library
find_package(Eigen3 3.4 REQUIRED NO_MODULE)
target_link_libraries(raytracer Eigen3::Eigen)

# yaml-cpp for config files
find_package(yaml-cpp REQUIRED)
target_link_libraries(raytracer yaml-cpp)

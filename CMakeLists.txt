cmake_minimum_required(VERSION 3.18)
project(computer_graphics)

set(CMAKE_CXX_STANDARD 14)


# Add header file
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include)
set(GLFW_H /usr/local/Cellar/glfw/3.3.6/include)
set(GLM /usr/local/Cellar/glm/0.9.9.8/include)
include_directories(${GLEW_H} ${GLFW_H} ${GLM})


# Link dynamic libraries to every target of a project
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.6/lib/libglfw.3.dylib)
# Create my own one library for GL support
add_library(GLSupport
    support/shader_loader.hpp
    support/shader_loader.cpp
    support/gl_manager.hpp
    support/gl_manager.cpp
)

link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} GLSupport)

# Make support library includes visible to Tasks
include_directories(support)


# Tasks subdirectories
add_subdirectory(Task1)
add_subdirectory(Task2)
add_subdirectory(Task3)


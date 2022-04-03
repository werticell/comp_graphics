cmake_minimum_required(VERSION 3.18)
project(computer_graphics)

set(CMAKE_CXX_STANDARD 14)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})


# Add header file
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.6/include/GLFW)
set(GLM /usr/local/Cellar/glm/0.9.9.8/include/glm)
include_directories(${GLEW_H} ${GLFW_H} ${GLM})


# Link dynamic libraries to every target of a project
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.6/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})


# Tasks subdirectories
add_subdirectory(Task1)



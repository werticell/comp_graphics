cmake_minimum_required(VERSION 3.18)
project(computer_graphics)

set(CMAKE_CXX_STANDARD 14)

if (APPLE)
  # Add header file
  set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include)
  set(GLFW_H /usr/local/Cellar/glfw/3.3.6/include)
  set(GLM /usr/local/Cellar/glm/0.9.9.8/include)
  include_directories(${GLEW_H} ${GLFW_H} ${GLM})


  set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
  set(GLFW_LINK /usr/local/Cellar/glfw/3.3.6/lib/libglfw.3.dylib)

  set(ALL_EXTERNAL_LIBS ${OPENGL} ${GLEW_LINK} ${GLFW_LINK})
elseif(UNIX)
  find_package(OpenGL REQUIRED)
  add_subdirectory(external)
  include_directories(
      external/glfw-3.1.2/include/
      external/glm-0.9.7.1/
      external/glew-1.13.0/include/
  )
  set(ALL_EXTERNAL_LIBS ${OPENGL_LIBRARY} glfw GLEW_1130)
endif()


# Create my own one library for GL support
add_library(GLSupport
    support/shader_loader.cpp
    support/gl_manager.cpp
    support/controls.cpp
    support/objloader.cpp
    support/text2D.cpp
    support/texture_loader.cpp
)

# Make support library includes visible to Tasks
include_directories(support)

# Link dynamic libraries to every target of a project
link_libraries(${ALL_EXTERNAL_LIBS} GLSupport)


# Tasks subdirectories
add_subdirectory(Task1)
add_subdirectory(Task2)
add_subdirectory(Task3)
add_subdirectory(Task4)

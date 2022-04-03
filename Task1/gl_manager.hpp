#pragma once

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

namespace framework {

class GlManager {
  static const int kWidth = 1024;
  static const int kHeight = 768;
  static const int kMajorVersion = 2;
  static const int kMinorVersion = 1;

 public:
  GlManager() = default;
  ~GlManager() {
    if (glfw_initialised_) {
      glfwTerminate();
    }
  }

  bool InitialiseGLFW() {
    glfw_initialised_ = glfwInit();
    return glfw_initialised_;
  }

  bool InitialiseGLEW() const {
    return glewInit() == GLEW_OK;
  }

  // Opens a window and creates its OpenGL context.
  // Returns nullptr on error.
  bool MakeWindow(std::string name) {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, kMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, kMinorVersion);

    window_ = glfwCreateWindow(kWidth, kHeight, name.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window_);
    return window_ != nullptr;
  }

  GLFWwindow* GetWindow() const {
    return window_;
  }

  bool ShouldQuit() const {
    return glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
           glfwWindowShouldClose(window_) != 0;
  }

 private:
  GLFWwindow* window_ = nullptr;
  bool glfw_initialised_ = false;
};

}  // namespace framework

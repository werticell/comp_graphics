#pragma once

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <string>
#include <vector>

namespace framework {

class GlManager {
  static const int kWidth = 1024;
  static const int kHeight = 768;
  static const int kMajorVersion = 2;
  static const int kMinorVersion = 1;

 public:
  enum BackgroundColors {
    kWhite,
    kDarkBlue,
  };

 public:
  GlManager() = default;
  ~GlManager() {
    if (glfw_initialised_) {
      glfwTerminate();
    }
    ClearBuffers();
  }

  bool InitialiseGLFW() {
    glfw_initialised_ = glfwInit();
    return glfw_initialised_;
  }

  bool InitialiseGLEW() const {
    return glewInit() == GLEW_OK;
  }

  // Opens a window and creates its OpenGL context.
  bool MakeWindow(std::string name);

  GLFWwindow* GetWindow() const {
    return window_;
  }

  bool ShouldQuit() const {
    return glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
           glfwWindowShouldClose(window_) != 0;
  }

  void EnableBlending() const {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void SetBackgroundColor(BackgroundColors color) const;

  // Ensures that we can capture the escape key.
  void CheckEscKey() const {
    glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);
  }

  void EnableLessDepthTest() const {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }

  GLuint MakeStaticDrawBuffer(const float data[], size_t data_size) {
    GLuint handler;
    glGenBuffers(1, &handler);
    glBindBuffer(GL_ARRAY_BUFFER, handler);
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
    buffer_handlers_.push_back(handler);
    return handler;
  }

 private:
  void ClearBuffers() {
    while (!buffer_handlers_.empty()) {
      GLuint handler = buffer_handlers_.back();
      buffer_handlers_.pop_back();
      glDeleteBuffers(1, &handler);
    }

  }

 private:
  GLFWwindow* window_ = nullptr;
  bool glfw_initialised_ = false;

  std::vector<GLuint> buffer_handlers_;
};

}  // namespace framework

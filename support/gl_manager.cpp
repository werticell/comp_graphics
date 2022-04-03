#include "gl_manager.hpp"

namespace framework {

bool GlManager::MakeWindow(std::string name) {
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, kMajorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, kMinorVersion);

  window_ = glfwCreateWindow(kWidth, kHeight, name.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(window_);
  return window_ != nullptr;
}

void GlManager::SetBackgroundColor(BackgroundColors color) const {
  switch (color) {
    case kWhite:
      glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
      break;
    case kDarkBlue:
      glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
      break;
  }
}

}  // namespace framework

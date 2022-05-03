#pragma once

class TextManager {
 public:
  TextManager(const char * path) {
    initText2D(path);
  }

  ~TextManager() {
    // Delete the text's VBO, the shader and the texture
    cleanupText2D();
  }

  void Display(uint64_t number) {
    std::string fireballs("Doggos fed: " + std::to_string(number));
    printText2D(fireballs.data(), 0, 550, 25);
  }

};
#pragma once

#include <text2D.hpp>

class TextManager {
 public:
  TextManager(const char* path, const char* text_vertex_shader,
              const char* text_fragment_shader) {
    support::InitText2D(path, text_vertex_shader, text_fragment_shader);
  }

  ~TextManager() {
    // Delete the text's VBO, the shader and the texture
    support::CleanupText2D();
  }

  void Display(uint64_t number) {
    std::string bone("Doggos fed: " + std::to_string(number));
    support::PrintText2D(bone.data(), 0, 550, 25);
    std::string cursor("+");
    support::PrintText2D(cursor.data(), 380, 275, 50);
  }
};
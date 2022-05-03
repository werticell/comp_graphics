#pragma once

#include <glm/glm.hpp>

class Doggo {
 public:
  Doggo();

  static void LoadDoggoObj(const char* filepath);

 public:
  static inline const float kDistanceToCollide = 1;

  std::vector<glm::vec3> vertices_;
  std::vector<glm::vec3> normals_;
  std::vector<glm::vec2> uvs_;
  glm::vec3 current_center{0, 0, 0};
};

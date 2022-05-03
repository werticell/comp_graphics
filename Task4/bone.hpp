#pragma once

#include <glm/glm.hpp>

class Bone {
 public:
  Bone(const glm::vec3& current_look_at);

  void UpdateLocation();


  static void LoadBoneObj(const char* filepath);

 public:
  std::vector<glm::vec3> vertices_;
  std::vector<glm::vec3> normals_;
  std::vector<glm::vec2> uvs_;
  glm::vec3 current_center{0, 0, 0};
  glm::vec3 direction;
  static inline const float kDistanceToCollide = 0.1f;
};

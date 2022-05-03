#pragma once

#include <glm/glm.hpp>

class Bone {
 public:
  Bone(const glm::vec3& current_look_at)
      : vertices_(fireball_obj_vertices),
        uvs_(fireball_obj_uvs),
        normals_(fireball_obj_normals) {
    glm::vec3 cur_position = GetPosition();

    glm::vec3 offset = glm::normalize(current_look_at) * 2.0f;
    offset[2] *= -1.0f;
    offset += cur_position;

    float angle = HorizontalAngle(current_look_at, kLookAt);
    glm::mat4 trans =
        glm::rotate(glm::mat4(1.0f), -angle, glm::vec3(0.0f, 1.0f, 0.0f));

    current_center += offset;
    for (glm::vec3& vertex : vertices_) {
      vertex = glm::vec3(trans * glm::vec4(vertex, 1));
      vertex += offset;
    }
    direction = current_center - cur_position;
    direction[1] = 0;
    direction *= 0.1f;
  }

  void UpdateLocation() {
    current_center += direction;
    for (glm::vec3& vertex : vertices_) {
      vertex += direction;
    }
  }

  static void LoadBoneObj(const char* filepath) {
    loadOBJ(filepath, fireball_obj_vertices, fireball_obj_uvs,
            fireball_obj_normals);
    RotateFireballObj();
  }

 public:
  std::vector<glm::vec3> vertices_;
  std::vector<glm::vec3> normals_;
  std::vector<glm::vec2> uvs_;
  glm::vec3 current_center{0, 0, 0};
  glm::vec3 direction;
  static inline const float kDistanceToCollide = 0.35f;

 private:
  static void RotateFireballObj() {
    glm::mat4 trans = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f),
                                  glm::vec3(0.0f, 1.0f, 0.0f));

    for (glm::vec3& vertex : fireball_obj_vertices) {
      vertex = glm::vec3(trans * glm::vec4(vertex, 1));
    }
  }

  float HorizontalAngle(glm::vec3 v1, glm::vec3 v2) {
    v1[1] = 0;
    v2[1] = 0;
    float angle = acos(glm::dot(glm::normalize(v1), glm::normalize(v2)));
    if (v1[0] * v2[2] - v1[2] * v2[0] < 0) {
      angle *= -1;
    }
    return angle;
  }

 private:
  static inline std::vector<glm::vec3> fireball_obj_vertices;
  static inline std::vector<glm::vec3> fireball_obj_normals;
  static inline std::vector<glm::vec2> fireball_obj_uvs;
  static inline const glm::vec3 kLookAt{0.0f, 0.0f, -1.0f};
};

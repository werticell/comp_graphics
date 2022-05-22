#pragma once

class Ground {

 public:

  Ground() : vertices_(default_vertices), normals_(default_normals), uvs_(default_uvs) {}

  static void LoadObj(const char* filepath) {
    support::LoadObj(filepath, default_vertices, default_uvs, default_normals);
  }

 public:
  std::vector<glm::vec3> vertices_;
  std::vector<glm::vec3> normals_;
  std::vector<glm::vec2> uvs_;
  glm::vec3 current_center{0, 0, 0};


 private:

  static inline std::vector<glm::vec3> default_vertices;
  static inline std::vector<glm::vec3> default_normals;
  static inline std::vector<glm::vec2> default_uvs;
};
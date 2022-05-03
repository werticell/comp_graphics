#pragma once

#include "bone.hpp"
#include "doggo.hpp"

class GameManager {
  static inline const int kMaxDistance = 30;
  static inline const int kEnemiesCountOnStart = 5;
  static inline const int kMaxEnemiesCount = 20;
  static inline const double kDoggoSpawnDelay = 2.0;
  static inline const double kBoneDelay = 0.5;

 public:
  void SetupWithDoggos() {
    for (size_t i = 0; i < kEnemiesCountOnStart; ++i) {
      CreateNewDoggo();
    }
    MakeContiguous();
  }

  void UpdateBonesLocation() {
    for (int k = 0; k < bones_.size(); ++k) {
      if (length(bones_[k].current_center) > kMaxDistance) {
        RemoveBone(k);
        --k;
      }
    }

    for (int k = 0; k < bones_.size(); ++k) {
      bones_[k].UpdateLocation();
    }
    CheckCollisions();
  }

  void MakeContiguous() {
    all_vertices_.clear();
    all_uvs_.clear();
    all_normals_.clear();
    for (Doggo& doggo : doggos_) {
      all_vertices_.insert(all_vertices_.end(), doggo.vertices_.begin(),
                           doggo.vertices_.end());
      all_normals_.insert(all_normals_.end(), doggo.normals_.begin(),
                          doggo.normals_.end());
      all_uvs_.insert(all_uvs_.end(), doggo.uvs_.begin(), doggo.uvs_.end());
    }
    for (Bone& bone : bones_) {
      all_vertices_.insert(all_vertices_.end(), bone.vertices_.begin(),
                           bone.vertices_.end());
      all_normals_.insert(all_normals_.end(), bone.normals_.begin(),
                          bone.normals_.end());
      all_uvs_.insert(all_uvs_.end(), bone.uvs_.begin(), bone.uvs_.end());
    }
  }

  void TryToAddDoggo() {
    double cur_time = glfwGetTime();
    if (cur_time - last_doggo_time_ > kDoggoSpawnDelay) {
      last_doggo_time_ = cur_time;
      if (doggos_count_ < kMaxEnemiesCount) {
        CreateNewDoggo();
      }
    }
  }

  void TryToThrowABone() {
    double cur_time = glfwGetTime();
    if (cur_time - last_bone_time_ > kBoneDelay) {
      last_bone_time_ = cur_time;
      ThrowABone();
    }
  }

  void ThrowABone() {
    ++bones_count_;
    Bone new_ball(cur_look_at_);
    bones_.push_back(new_ball);
  }

  void SetCurrentLookAt(glm::vec3 other) {
    cur_look_at_ = other;
  }

  // Getters.
  //////////////////////////////////////////////////////////////////////////////
  int GetDoggosFedCount() const {
    return doggo_fed_;
  }

  std::vector<glm::vec3>& GetAllVertices() {
    return all_vertices_;
  }

  std::vector<glm::vec3>& GetAllNormals() {
    return all_normals_;
  }

  std::vector<glm::vec2>& GetAllUvs() {
    return all_uvs_;
  }

 private:
  void CreateNewDoggo() {
    Doggo new_enemy;
    doggos_.push_back(new_enemy);
    ++doggos_count_;
  }

  void RemoveDoggo(int k) {
    doggos_.erase(doggos_.begin() + k);
    --doggos_count_;
  }

  void RemoveBone(int k) {
    bones_.erase(bones_.begin() + k);
  }

  void CheckCollisions() {
    for (int f = 0; f < bones_.size(); ++f) {
      for (int e = 0; e < doggos_.size(); ++e) {
        if (distance(bones_[f].current_center, doggos_[e].current_center) <
            bones_[f].kDistanceToCollide + doggos_[e].kDistanceToCollide) {
          ++doggo_fed_;
          RemoveDoggo(e);
          RemoveBone(f);
          CreateNewDoggo();
          --f;
          break;
        }
      }
    }
  }

 private:
  glm::vec3 cur_look_at_{1.0f, 0.0f, 1.0f};
  std::vector<Bone> bones_;
  std::vector<Doggo> doggos_;
  int64_t bones_count_ = 0;
  int64_t doggo_fed_ = 0;
  int64_t doggos_count_ = 0;

  std::vector<glm::vec3> all_vertices_;
  std::vector<glm::vec3> all_normals_;
  std::vector<glm::vec2> all_uvs_;

  // To make some delay for shooting and spawning new doggos.
  double last_bone_time_ = 0;
  double last_doggo_time_ = 0;
};
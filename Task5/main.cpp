#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <texture_loader.hpp>
#include <controls.hpp>

#include "game_manager.hpp"
#include "gl_manager.hpp"
#include "text_manager.hpp"
//#include "ground.hpp"

using Colors = support::GlManager::BackgroundColors;

GameManager game_manager;

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    game_manager.ThrowABone();
  }
}

int main() {
  support::GlManager manager;

  if (!manager.InitialiseGLFW() || !manager.MakeWindow("FeedTheDoggo3D") ||
      !manager.InitialiseGLEW()) {
    std::cout << "Failed to initialize. Closing...";
    return 1;
  }

  manager.CheckEscKey();
  manager.SetBackgroundColor(Colors::kLightBlue);
  manager.EnableLessDepthTest();
  manager.SetupCursor();
  glEnable(GL_CULL_FACE);

  GLuint vertex_array_id;
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);

  // Compile shader programmes.
  GLuint program_id = manager.LoadShaders("VertexStandardShading.glsl",
                                          "FragmentStandardShading.glsl");

  // Get a handle for our "MVP" variable from shader.
  GLuint mvp_matrix_id = glGetUniformLocation(program_id, "MVP");
  GLuint view_matrix_id = glGetUniformLocation(program_id, "V");
  GLuint model_matrix_id = glGetUniformLocation(program_id, "M");

  // Load textures for doggos and bones.
  GLuint bone_texture = support::LoadDds("bone_texture.dds");
  GLuint doggo_texture = support::LoadDds("doggo_texture.dds");

  // Get a handle for our "myTextureSampler" variable from shader.
  GLuint texture_id = glGetUniformLocation(program_id, "myTextureSampler");

  // Read our obj files to set default vertices of our objects.
  Doggo::LoadDoggoObj("doggo.obj");
  Bone::LoadBoneObj("bone.obj");
  Ground::LoadObj("grass.obj");

  // Spawn starting doggos
  game_manager.SetupScene();

  glUseProgram(program_id);
  GLuint light_id =
      glGetUniformLocation(program_id, "LightPosition_worldspace");

  TextManager text_manager("Holstein.DDS", "TextVertexShader.glsl", "TextFragmentShader.glsl");

  manager.SetMouseButtonCallback(MouseButtonCallback);
  while (!manager.ShouldQuit()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program_id);

    // Compute the MVP matrix from keyboard and mouse input.
    support::ComputeMatricesFromInputs(manager.GetWindow());
    glm::mat4 projection_matrix = support::GetProjectionMatrix();
    glm::mat4 view_matrix = support::GetViewMatrix();
    glm::mat4 model_matrix = glm::mat4(1.0);
    glm::mat4 mvp = projection_matrix * view_matrix * model_matrix;

    // Get the 3-rd column - the forward direction for bones direction.
    game_manager.SetCurrentLookAt(glm::vec3(view_matrix[2]));

    game_manager.TryToAddDoggo();
    if (manager.IsPressed(GLFW_MOUSE_BUTTON_LEFT)) {
      game_manager.TryToThrowABone();
    }
    game_manager.UpdateBonesLocation();

    // Move mvp data to shaders.
    glUniformMatrix4fv(mvp_matrix_id, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, &model_matrix[0][0]);
    glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, &view_matrix[0][0]);

    glm::vec3 light_pos = glm::vec3(0, 7, 0);
    glUniform3f(light_id, light_pos.x, light_pos.y, light_pos.z);

    // Set texture for Doggos.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, doggo_texture);
    glUniform1i(texture_id, 0);

    game_manager.DrawDoggos(manager);

    // Set texture for Bones.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bone_texture);
    glUniform1i(texture_id, 0);

    game_manager.DrawBones(manager);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    text_manager.Display(game_manager.GetDoggosFedCount());

    // Swap buffers
    glfwSwapBuffers(manager.GetWindow());
    glfwPollEvents();
  }

  // Cleanup VBO and shader

  glDeleteTextures(1, &bone_texture);
  glDeleteTextures(1, &doggo_texture);
  glDeleteVertexArrays(1, &vertex_array_id);
  return 0;
}
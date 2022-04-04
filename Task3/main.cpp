#include "vertex_buffer_data.hpp"

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <shader_loader.hpp>
#include <gl_manager.hpp>

#include <iostream>

using Colors = framework::GlManager::BackgroundColors;

int main() {
  framework::GlManager manager;

  if (!manager.InitialiseGLFW() || !manager.MakeWindow("Task3") ||
      !manager.InitialiseGLEW()) {
    std::cout << "Failed to initialize. Closing...";
    return 1;
  }

  manager.CheckEscKey();
  manager.SetBackgroundColor(Colors::kWhite);
  manager.EnableBlending();
  manager.EnableLessDepthTest();

  // Create and compile our GLSL programs from the shaders.
  GLuint program_id =
      framework::LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");

  // Get handles to MVP variable in shader.
  GLuint mvp_matrix = glGetUniformLocation(program_id, "MVP");

  GLuint vertex_buffer = manager.MakeStaticDrawBuffer(
      kVertexBufferData, sizeof(kVertexBufferData));
  GLuint color_buffer = manager.MakeStaticDrawBuffer(
      kColorBufferData, sizeof(kColorBufferData));

  // Model matrix. For both triangles is the same - models remain unchanged.
  glm::mat4 model = glm::mat4(1.0f);

  // View matrix. Will change every frame.
  glm::mat4 view;

  // Projection matrix.
  // Field of view - 45deg
  // Ratio - 4:3 for 1024:768 window
  // Range - 0.1 Unit -> 100 Unit
  glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

  // MVP matrix to pass to our shader.
  glm::mat4 mvp;

  // Will be rotated along x and z axis.
  glm::vec4 current_camera_pos = glm::vec4(0, 0, -15, 1);
  // Matrix that rotates the camera.
  glm::mat4 rotation_matrix =
      glm::rotate(glm::mat4(1.0f),      // Identity matrix
                  0.03f,                // Angle in radians
                  glm::vec3(0, 1, 0));  // Axis of rotation

  while (!manager.ShouldQuit()) {
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate camera a bit.
    current_camera_pos = rotation_matrix * current_camera_pos;

    // Find current View matrix.
    view = glm::lookAt(glm::vec3(current_camera_pos),  // Position in world.
                       glm::vec3(0, 0, 0),             // Point to look at.
                       glm::vec3(0, 1, 0)          // Up head direction.
    );

    mvp = projection * view * model;

    glUseProgram(program_id);
    glUniformMatrix4fv(mvp_matrix, 1, GL_FALSE, &mvp[0][0]);

    // 1-st attribute buffer - vertices.
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // 2-nd attribute - color
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Draws octahedron.
    glDrawArrays(GL_TRIANGLES, 0, 3 * 8);

    glDisableVertexAttribArray(0);

    // Swap buffers.
    glfwSwapBuffers(manager.GetWindow());
    glfwPollEvents();
  }

  glDeleteProgram(program_id);
  return 0;
}

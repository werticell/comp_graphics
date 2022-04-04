#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <gtc/matrix_transform.hpp>

#include <gl_manager.hpp>

#include <iostream>

using Colors = framework::GlManager::BackgroundColors;

int main() {
  framework::GlManager manager;

  if (!manager.InitialiseGLFW() || !manager.MakeWindow("Task2") ||
      !manager.InitialiseGLEW()) {
    std::cout << "Failed to initialize. Closing...";
    return 1;
  }

  manager.CheckEscKey();
  manager.SetBackgroundColor(Colors::kWhite);
  manager.EnableBlending();

  // Compile GLSL programs from the sources.
  GLuint program_id1 =
      manager.LoadShaders("vertex_shader.glsl", "fragment_shader1.glsl");
  GLuint program_id2 =
      manager.LoadShaders("vertex_shader.glsl", "fragment_shader2.glsl");

  // Get handles to MVP variable in shader.
  GLuint mvp_matrix1 = glGetUniformLocation(program_id1, "MVP");
  GLuint mvp_matrix2 = glGetUniformLocation(program_id2, "MVP");

  // Create vertex buffer data.
  static const GLfloat kVertexBufferData[] = {
      -0.5f, 0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      0.0f, -0.2f, 0.0f,

      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.2f, 0.0f,
  };

  GLuint vertex_buffer = manager.MakeStaticDrawBuffer(
      kVertexBufferData, sizeof(kVertexBufferData));

  // Model matrix. For both triangles is the same - models remain unchanged.
  glm::mat4 model = glm::mat4(1.0f);

  // View matrix. Will change every frame.
  glm::mat4 view;

  // Projection matrix.
  // Field of view - 45deg.
  // Ratio - 4:3 for 1024:768 window.
  // Range - 0.1 Unit -> 100 Unit.
  glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

  // MVP matrix to pass to our shader.
  glm::mat4 mvp;

  // Will be rotated along x and z axis.
  glm::vec4 current_camera_pos = glm::vec4(0, 0, -4, 1);
  // Matrix that rotates the camera.
  glm::mat4 rotation_matrix =
      glm::rotate(glm::mat4(1.0f),      // Identity matrix
                  0.03f,                // Angle in radians
                  glm::vec3(0, 1, 0));  // Axis of rotation

  while (!manager.ShouldQuit()) {
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    // Rotate camera a bit.
    current_camera_pos = rotation_matrix * current_camera_pos;

    // Find current View matrix.
    view = glm::lookAt(glm::vec3(current_camera_pos),  // Position in world.
                       glm::vec3(0, 0, 0),             // Point to look at.
                       glm::vec3(0.4, 1, 0.3)          // Up head direction.
    );

    mvp = projection * view * model;

    // 1-st attribute buffer - vertices.
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Draws two triangles from current camera view.
    glUseProgram(program_id1);
    glUniformMatrix4fv(mvp_matrix1, 1, GL_FALSE, &mvp[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(program_id2);
    glUniformMatrix4fv(mvp_matrix2, 1, GL_FALSE, &mvp[0][0]);
    glDrawArrays(GL_TRIANGLES, 3, 6);

    glDisableVertexAttribArray(0);

    // Swap buffers.
    glfwSwapBuffers(manager.GetWindow());
    glfwPollEvents();
  }

  return 0;
}

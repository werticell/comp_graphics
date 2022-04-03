#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include "../support/shader.hpp"
#include "gl_manager.hpp"

#include <iostream>

int main() {
  framework::GlManager manager;

  if (!manager.InitialiseGLFW() || !manager.MakeWindow("Task1") ||
      !manager.InitialiseGLEW()) {
    std::cout << "Failed to initialize. Closing...";
    return 1;
  }
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(manager.GetWindow(), GLFW_STICKY_KEYS, GL_TRUE);

  // White background color
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  // Enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Create and compile our GLSL programs from the shaders
  GLuint program_id1 = framework::LoadShaders2("vertex_shader.glsl", "fragment_shader1.glsl");
  GLuint program_id2 = framework::LoadShaders2("vertex_shader.glsl", "fragment_shader2.glsl");


  static const GLfloat kVertexBufferData[] = {
      -0.5f, 0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      0.0f, -0.2f, 0.0f,

      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.2f, 0.0f,
  };

  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(kVertexBufferData), kVertexBufferData, GL_STATIC_DRAW);

  // Wait for ESC to be pressed
  while (!manager.ShouldQuit()) {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);


    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Uses shader1 and draws first triangle (from 0 to 3 vertices)
    glUseProgram(program_id1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Uses shader2 and draws first triangle (from 3 to 6 vertices)
    glUseProgram(program_id2);
    glDrawArrays(GL_TRIANGLES, 3, 6);


    glDisableVertexAttribArray(0);

    // Swap buffers
    glfwSwapBuffers(manager.GetWindow());
    glfwPollEvents();
  }

  // Cleanup VBO
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteProgram(program_id1);
  glDeleteProgram(program_id2);

  return 0;
}

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <shader_loader.hpp>
#include <gl_manager.hpp>

#include <iostream>

using Colors = framework::GlManager::BackgroundColors;

int main() {
  framework::GlManager manager;

  if (!manager.InitialiseGLFW() || !manager.MakeWindow("Task1") ||
      !manager.InitialiseGLEW()) {
    std::cout << "Failed to initialize. Closing...";
    return 1;
  }
  manager.CheckEscKey();
  manager.SetBackgroundColor(Colors::kWhite);
  manager.EnableBlending();

  // Create and compile our GLSL programs from the shaders
  GLuint program_id1 =
      framework::LoadShaders("vertex_shader.glsl", "fragment_shader1.glsl");
  GLuint program_id2 =
      framework::LoadShaders("vertex_shader.glsl", "fragment_shader2.glsl");

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
  
  glDeleteProgram(program_id1);
  glDeleteProgram(program_id2);

  return 0;
}

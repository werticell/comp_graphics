#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

  // Compile GLSL programs from the sources.
  GLuint program_id1 =
      manager.LoadShaders("vertex_shader.glsl", "fragment_shader1.glsl");
  GLuint program_id2 =
      manager.LoadShaders("vertex_shader.glsl", "fragment_shader2.glsl");

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

  while (!manager.ShouldQuit()) {
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    // 1-st attribute buffer - vertices.
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Uses shader1 and draws first triangle (from 0 to 3 vertices).
    glUseProgram(program_id1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Uses shader2 and draws first triangle (from 3 to 6 vertices).
    glUseProgram(program_id2);
    glDrawArrays(GL_TRIANGLES, 3, 6);

    glDisableVertexAttribArray(0);

    // Swap buffers.
    glfwSwapBuffers(manager.GetWindow());
    glfwPollEvents();
  }

  return 0;
}

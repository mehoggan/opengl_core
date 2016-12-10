#include "opengl_core/core/render_system.h"
#include "opengl_core/core/x11/x11_gl_functions.h"

#include <cstdint>
#include <iostream>
#include <thread>

void init_function(opengl_core::render_system &system)
{
  std::cout << "Init" << std::endl;
}

void pre_render_function(opengl_core::render_system &system)
{
}

void render_function(opengl_core::render_system &system, std::size_t millis)
{
  static bool init = false;
  if (!init) {
    init = true;
    const GLchar* vertexSource =
      "#version 150 core\n"
      "in vec2 position;"
      "void main()"
      "{"
      "    gl_Position = vec4(position, 0.0, 1.0);"
      "}";
    const GLchar* fragmentSource =
      "#version 150 core\n"
      "out vec4 outColor;"
      "void main()"
      "{"
      "    outColor = vec4(1.0, 1.0, 1.0, 1.0);"
      "}";

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat vertices[] = {
      +0.0f, +0.5f,
      +0.5f, -0.5f,
      -0.5f, -0.5f
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  }
  // Draw a triangle from the 3 vertices
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void post_render_function(opengl_core::render_system &system)
{
}

void shutdown_function(opengl_core::render_system &system)
{
  std::cout << "Shutdown" << std::endl;
}

int main(int argc, char *argv[])
{
  opengl_core::render_system::init_function init = std::bind(
    &init_function, std::placeholders::_1);
  opengl_core::render_system::pre_render_function pre = std::bind(
    &pre_render_function, std::placeholders::_1);
  opengl_core::render_system::render_function renderer = std::bind(
    &render_function, std::placeholders::_1, std::placeholders::_2);
  opengl_core::render_system::post_render_function post = std::bind(
    &post_render_function, std::placeholders::_1);
  opengl_core::render_system::shutdown_function shutdown = std::bind(
    &shutdown_function, std::placeholders::_1);

  opengl_core::render_system render_system(init, pre, renderer, post,
    shutdown, false);
  render_system.init_system();
  render_system.destroy();

  return 0;
}

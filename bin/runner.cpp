#include "opengl_core/core/draw_buffer_context.h"
#include "opengl_core/core/draw_buffer_window_config.h"
#include "opengl_core/core/init.h"
#include "opengl_core/core/standard_renderer.h"
#include "opengl_core/core/x11/x11_gl_functions.h"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <thread>
#include <vector>


void thread_func(int x, int y, int w, int h);

int main(int argc, char * argv[])
{
  bool init_status = opengl_core::init();
  if (!init_status) {
    std::cerr << "Failed to init all systems." << std::endl << std::flush;
    exit(-1);
  }

  std::vector<std::thread> threads;
  threads.resize(2);
  for (int i = 0; i < threads.size(); ++i) {
    threads[i] = std::thread(std::bind(&thread_func, std::rand() % 100,
      std::rand() % 100, 800, 600));
  }

  for (auto &thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

void init(opengl_core::draw_buffer_window &win,
  opengl_core::draw_buffer_context &ctx);
void render(opengl_core::draw_buffer_window &win,
  opengl_core::draw_buffer_context &ctx);

void thread_func(int x, int y, int w, int h)
{
  const opengl_core::gl_version ctx_ver = {4, 2};
  opengl_core::set_thread_local_init_callback(std::bind(&init,
    std::placeholders::_1, std::placeholders::_2));
  opengl_core::set_thread_local_render_callback(std::bind(&render,
    std::placeholders::_1, std::placeholders::_2));
  opengl_core::standard_event_loop_run(ctx_ver,
    opengl_core::draw_buffer_window_config(x, y, w, h));
}

GLuint vao;
GLuint vbo;
GLuint shaderProgram;

bool compiler_errors(GLuint shaderId)
{
  bool errors = false;

  GLint isCompiled = 0;

  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    GL_CALL("glGetShaderiv")
  if(isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
      GL_CALL("glGetShaderiv")
    std::vector<char> errorLog(maxLength);
    glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
      GL_CALL("glGetShaderInfoLog")
    std::stringstream out;
    std::copy(errorLog.begin(), errorLog.end(), std::ostream_iterator<char>(
      out, ""));
    std::string errorsStr = out.str();
    std::cerr << "Shader Compiler Erros " << errorsStr.c_str();
    errors = true;
  }

  return errors;
}

void init(opengl_core::draw_buffer_window &win,
  opengl_core::draw_buffer_context &ctx)
{
  const GLchar* vertexSource =
    "#version 150 core\n"
    "in vec2 position;"
    "void main()"
    "{"
    "  gl_Position = vec4(position, 0.0, 1.0);"
    "}";
  const GLchar* fragmentSource =
    "#version 150 core\n"
    "out vec4 outColor;"
    "void main()"
    "{"
    "  outColor = vec4(1.0, 1.0, 1.0, 1.0);"
    "}";

  glGenBuffers(1, &vbo); GL_CALL(glGenBuffers)

  GLfloat vertices[] = {
    +0.0f, +0.5f,
    +0.5f, -0.5f,
    -0.5f, -0.5f
  };

  opengl_core::gl_version v =
    opengl_core::draw_buffer_context_version(ctx, win);
  if (v.major >= 3 && v.minor >= 2) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo); GL_CALL(glBindBuffer)
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
    GL_STATIC_DRAW); GL_CALL(glBufferData)

  // Create and compile the vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GL_CALL(glCreateShader)
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
    GL_CALL(glShaderSource)
  glCompileShader(vertexShader);
    GL_CALL(glCompileShader)

  if(compiler_errors(vertexShader) == GL_TRUE) {
    throw std::runtime_error("Failed to compile vertex shader.");
  }

  // Create and compile the fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GL_CALL(glCreateShader)
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    GL_CALL(glShaderSource);
  glCompileShader(fragmentShader);
    GL_CALL(glCompileShader);
  if(compiler_errors(fragmentShader) == GL_TRUE) {
    throw std::runtime_error("Failed to compile fragment shader.");
  }

  // Link the vertex and fragment shader into a shader program
  shaderProgram = glCreateProgram();
    GL_CALL(glCreateProgram)
  glAttachShader(shaderProgram, vertexShader);
    GL_CALL(glAttachShader);
  glAttachShader(shaderProgram, fragmentShader);
    GL_CALL(glAttachShader);
  glLinkProgram(shaderProgram);
    GL_CALL(glLinkProgram);
  glUseProgram(shaderProgram);
    GL_CALL(glUseProgram);
}

void render(opengl_core::draw_buffer_window &win,
  opengl_core::draw_buffer_context &ctx)
{
  glViewport(0, 0, 800, 600); GL_CALL(glViewport)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CALL(glClear)

  // Clear the screen to black
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GL_CALL("glClearColor")
  glClear(GL_COLOR_BUFFER_BIT);
    GL_CALL("glClear(GL_COLOR_BUFFER_BIT)")

  // Draw a triangle from the 3 vertices
  glUseProgram(shaderProgram);
    GL_CALL("glUseProgram")
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GL_CALL("glBindBuffer")

  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    GL_CALL("glGetAttribLocation")
  glEnableVertexAttribArray(posAttrib);
    GL_CALL("glEnableVertexAttribArray")
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    GL_CALL("glVertexAttribPointer")
  glDrawArrays(GL_TRIANGLES, 0, 3);
    GL_CALL("glDrawArrays")
}

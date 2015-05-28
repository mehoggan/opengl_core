#include <test_render_system.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

bool test_render_system::run()
{
  opengl_core::render_system render_system;
  render_system.init();
  render_system.run(false);

  std::cout << "Start Testing a glIsShader" << std::endl;
  GLboolean is_shader = glIsShader(0);
  OPENGL_CORE_ASSERT(is_shader == GL_FALSE);
  std::cout << "Done Testing a glIsShader" << std::endl;

  render_system.destroy();
}

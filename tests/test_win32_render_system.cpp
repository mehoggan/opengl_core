#include <test_render_system.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

bool test_render_system::run()
{
  opengl_core::render_system render_system;
  render_system.init();
  render_system.run(false);

  GLboolean is_shader = glIsShader(0);
  OPENGL_CORE_ASSERT(is_shader == GL_FALSE);

  render_system.destroy();

  return true;
}

#include <test_render_system.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

bool test_render_system::run()
{
  opengl_core::render_system render_system;
  render_system.init();
  render_system.destroy();
  return true;
}

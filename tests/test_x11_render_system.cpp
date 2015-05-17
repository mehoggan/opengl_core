#include <test_render_system.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

bool test_render_system::run()
{
  opengl_core::render_system::init();
  // If you do not destroy next test will fail.
  opengl_core::render_system::destroy();
}

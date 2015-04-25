#include <test_render_system.h>

#include <iostream>

bool test_render_system::run()
{
  opengl_core::render_system::init(1, 4);
  // If you do not destroy next test will fail.
  opengl_core::render_system::destroy();
}

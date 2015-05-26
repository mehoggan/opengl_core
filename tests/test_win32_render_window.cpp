#include <test_render_window.h>

#include <core/fb_config.h>
#include <core/render_window.h>

#include <chrono>
#include <thread>

bool test_render_window::run()
{
  // Because of a dependency on a context being current this test would be
  // duplicated by render_context tests.
  return true;
}

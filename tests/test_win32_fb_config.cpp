#include <test_fb_config.h>

#include <core/fb_config.h>
#include <core/render_window.h>

#include <cstring>
#include <iostream>

bool test_fb_config::run()
{
  // Because of a dependency on a context this test would be duplicated in
  // render context test.
  return true;
}

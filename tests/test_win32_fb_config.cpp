#include <test_fb_config.h>

#include <core/fb_config.h>

#include <cstring>
#include <iostream>

bool test_fb_config::run()
{
  opengl_core::fb_config frame_buffer_conf;
  frame_buffer_conf.choose_best();
  return true;
}

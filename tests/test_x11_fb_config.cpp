#include <test_fb_config.h>

#include <cstring>
#include <iostream>

#include <X11/Xlib.h>
#include <GL/glx.h>

bool test_fb_config::run()
{
  opengl_core::fb_config frame_buffer_conf;

  GLXFBConfig *config_impl =
    static_cast<GLXFBConfig*>(frame_buffer_conf.impl());
  OPENGL_CORE_ASSERT(config_impl && "Hmmmm. This should never be NULL");

  GLXFBConfig test;
  memset(&test, 0, sizeof(GLXFBConfig));

  // After creation the impl object should be in its default state.
  OPENGL_CORE_ASSERT(memcmp(config_impl, &test, sizeof(GLXFBConfig)) == 0 &&
    "Intilization of opengl_core::fb_config failed");

  frame_buffer_conf.choose_best(1, 0);

  // After we choose the best config
  OPENGL_CORE_ASSERT(memcmp(config_impl, &test, sizeof(GLXFBConfig)) != 0 &&
    "Choosing best frame buffer config for opengl_core::fb_config failed");

}

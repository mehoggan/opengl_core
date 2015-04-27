#include <test_fb_config.h>

#include <core/fb_config.h>

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

  // After creation of fb_config impl is zeroed out. We are verifying that
  // a know zeroed out version of the impl are equivalent here.
  OPENGL_CORE_ASSERT(memcmp(config_impl, &test, sizeof(GLXFBConfig)) == 0 &&
    "Intilization of opengl_core::fb_config failed");

  frame_buffer_conf.choose_best();

  // After we choose the best config the impl of a fb_config should not be 0
  OPENGL_CORE_ASSERT(memcmp(config_impl, &test, sizeof(GLXFBConfig)) != 0 &&
    "Choosing best frame buffer config for opengl_core::fb_config failed");
}

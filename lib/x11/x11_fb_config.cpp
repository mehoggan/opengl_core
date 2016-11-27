#include "opengl_core/core/fb_config.h"

#include "opengl_core/core/render_system.h"
#include "opengl_core/core/render_window.h"
#include "opengl_core/core/x11_display.h"

#include <cassert>
#include <cstring>
#include <limits>
#include <iomanip>
#include <iostream>

#include <X11/Xlib.h>
#include <GL/glx.h>

namespace opengl_core
{
  const int fb_attrib[] = {
    GLX_X_RENDERABLE, True,
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
    GLX_RED_SIZE, 8,
    GLX_GREEN_SIZE, 8,
    GLX_BLUE_SIZE, 8,
    GLX_ALPHA_SIZE, 8,
    GLX_DEPTH_SIZE, 24,
    GLX_STENCIL_SIZE, 8,
    GLX_DOUBLEBUFFER, True,
    None
  };

  struct fb_config::fb_config_impl
  {
    GLXFBConfig m_best_config;

    fb_config_impl()
    {
      memset(&m_best_config, 0, sizeof(GLXFBConfig));
    }
  };

  fb_config::fb_config() :
    m_impl(new fb_config::fb_config_impl)
  {}

  fb_config::~fb_config()
  {
    delete m_impl;
  }

  void fb_config::choose_best(render_system &, render_window *)
  {
    Display *&display = x11_display::acquire();

    int fb_config_count = -1;

    GLXFBConfig *confs = glXChooseFBConfig(display, DefaultScreen(display),
      fb_attrib, &fb_config_count);
    if (!confs) {
      std::cerr << "Failed to retrieve a framebuffer confs" << std::endl;
      x11_display::release();
      assert(confs);
    } else {
      std::cout << "Found " << fb_config_count << " matching FB confs."
        << std::endl;
    }

    int best_fbc = std::numeric_limits<int>::min();
    int best_num_samp = std::numeric_limits<int>::min();

    for (int i = 0; i < fb_config_count; ++i) {
      XVisualInfo *vi = glXGetVisualFromFBConfig(display, confs[i]);
      if (vi) {
        int samp_buf;
        int samples;
        glXGetFBConfigAttrib(display, confs[i], GLX_SAMPLE_BUFFERS, &samp_buf);
        glXGetFBConfigAttrib(display, confs[i], GLX_SAMPLES, &samples);
        std::cout << "Matching fbconfig " << i << " visual ID 0x" << std::hex
          << std::setw(2) << (vi->visualid) << ": SAMPLE_BUFFERS = "
          << samp_buf << " SAMPLES = " << samples << std::endl;

        if ((best_fbc < 0 || samp_buf) && (samples > best_num_samp)) {
          best_fbc = i;
          best_num_samp = samples;
        }
      }
      XFree(vi);
    }

    m_impl->m_best_config = confs[best_fbc];

    XFree(confs);
    x11_display::release();
  }

  void *fb_config::impl()
  {
    return (void*)(&(m_impl->m_best_config));
  }

  void fb_config::destroy()
  {
  }
}

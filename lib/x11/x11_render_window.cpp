#include "opengl_core/core/render_window.h"

#include "opengl_core/core/x11/x11_display.h"
#include "opengl_core/core/x11/x11_event_mask.h"

#include <cassert>
#include <iomanip>
#include <iostream>

#include <X11/Xlib.h>
#include <GL/glx.h>

namespace opengl_core
{
  struct render_window::window_impl
  {
    Window m_window;

    window_impl() :
      m_window(0)
    {}
  };

  render_window::render_window() :
    m_impl(new render_window::window_impl)
  {}

  render_window::~render_window()
  {
    delete m_impl;
  }

  void render_window::init_window(render_system &, fb_config &fbc)
  {
    Display *&display = x11_display::acquire();
    GLXFBConfig &config = *(static_cast<GLXFBConfig*>(fbc.impl()));

    XVisualInfo *vi = glXGetVisualFromFBConfig(display, config);
    std::cout << "Chosen visual ID = 0x" << std::hex << std::setw(3)
      << std::setfill('0') << vi->visualid << std::dec << std::endl;
    XSetWindowAttributes swa;
    swa.colormap = XCreateColormap(display, RootWindow(display, vi->screen),
      vi->visual, AllocNone);
    swa.background_pixmap = None;
    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;

    m_impl->m_window = XCreateWindow(
      display,
      RootWindow(display, vi->screen),
      0, 0, 100, 100,
      0,
      vi->depth,
      InputOutput,
      vi->visual,
      CWBorderPixel|CWColormap|CWEventMask,
      &swa);

    XSelectInput(display, m_impl->m_window, events::mask);

    XFree(vi);
    if (!m_impl->m_window) {
      x11_display::release();
      assert(m_impl->m_window && "Failed to create X11 window");
    }

    x11_display::release();
  }

  void render_window::map()
  {
    Display *&display = x11_display::acquire();
    XMapWindow(display, m_impl->m_window);
    x11_display::release();
  }

  void render_window::destroy()
  {
    Display *&display = x11_display::acquire();
    if (m_impl->m_window) {
      XDestroyWindow(display, m_impl->m_window);
    }
    x11_display::release();
  }

  void *render_window::impl()
  {
    return (void*)(&(m_impl->m_window));
  }
}

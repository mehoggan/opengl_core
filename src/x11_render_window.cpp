#include <core/render_window.h>

#include <core/x11_display.h>

#include <cassert>
#include <unistd.h>
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
  {}

  void render_window::init(fb_config &fbc)
  {
    Display *&display = x11_display::acquire();
    GLXFBConfig &config = *(static_cast<GLXFBConfig*>(fbc.impl()));
    std::cout << "Acquired Display " << (&display) << std::endl;

    XVisualInfo *vi = glXGetVisualFromFBConfig(display, config);
    std::cout << "Chosen visual ID = 0x" << std::hex << std::setw(3)
      << std::setfill('0') << vi->visualid << std::dec << std::endl;
    XSetWindowAttributes swa;
    swa.colormap = XCreateColormap(display, RootWindow(display, vi->screen),
      vi->visual, AllocNone);
    swa.background_pixmap = None;
    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;

    Window w = m_impl->m_window = XCreateWindow(
      display,
      RootWindow(display, vi->screen),
      0, 0, 100, 100,
      0,
      vi->depth,
      InputOutput,
      vi->visual,
      CWBorderPixel|CWColormap|CWEventMask,
      &swa);


    XFree(vi);
    if (!m_impl->m_window) {
      x11_display::release();
      assert(m_impl->m_window && "Failed to create X11 window");
    }
    std::cout << "Created Window " << m_impl->m_window << std::endl;

    x11_display::release();
  }

  void render_window::map()
  {
    Display *&display = x11_display::acquire();
    std::cout << "Mapping Window " << m_impl->m_window << std::endl;
    XMapWindow(display, m_impl->m_window);
    sleep(5);
    x11_display::release();
  }

  void render_window::destroy()
  {
    Display *&display = x11_display::acquire();
    if (m_impl->m_window) {
      std::cout << "Destroying Window " << m_impl->m_window << std::endl;
      XDestroyWindow(display, m_impl->m_window);
    }
    x11_display::release();
  }

  void *render_window::impl()
  {
    return (void*)(&(m_impl->m_window));
  }
}

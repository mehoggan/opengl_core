#include <core/render_system.h>

#include <core/fb_config.h>
#include <core/gl_functions.h>
#include <core/x11_display.h>

#include <chrono>
#include <iostream>
#include <thread>

#include <X11/Xlib.h>
#include <GL/glx.h>

namespace opengl_core
{
  struct render_system::render_system_impl
  {
    render_context m_context;
    render_window m_window;
    fb_config m_fbc;
  };

  render_system::render_system() :
    m_impl(new render_system_impl)
  {}

  render_system::~render_system()
  {
    delete m_impl;
  }

  bool render_system::init()
  {
    XInitThreads();

    Display *&display = opengl_core::x11_display::acquire();

    // Set to 0 because this would be the initial version.
    // Negagive numbers do not make since here.
    int glx_major = 0;
    int glx_minor = 0;
    if (!glXQueryVersion(display, &glx_major, &glx_minor)) {
      std::cerr << "Failed to query glx version" << std::endl;
      destroy();
      return false;
    }

    // According to https://www.opengl.org/sdk/docs/man2/xhtml/
    // glXIntro.xml glxQueryVersion returns both client and server.
    // However, according // to https://www.opengl.org/sdk/docs/man2/
    // xhtml/glXQueryVersion.xml it only returns the server version
    // string.
    std::cout << "server glx version string " << glx_major << "." <<
      glx_minor << std::endl;
    std::cout << "client glx version string " << glx_major << "." <<
      glx_minor << std::endl;

    m_impl->m_fbc.choose_best();

    m_impl->m_window.init(m_impl->m_fbc);
    m_impl->m_window.map();

    m_impl->m_context.init(m_impl->m_window, m_impl->m_fbc);
    m_impl->m_context.make_current(m_impl->m_window);

    gl_functions::configure(m_impl->m_context);
  }

  void render_system::run(bool threaded)
  {
    if (threaded) {
    } else {
    }
  }

  void render_system::destroy()
  {
    m_impl->m_context.make_not_current();
    m_impl->m_context.destroy();
    m_impl->m_window.destroy();
    x11_display::release();
  }
}

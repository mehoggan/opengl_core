#include "opengl_core/core/render_system.h"

#include "opengl_core/core/fb_config.h"
#include "opengl_core/core/render_context.h"
#include "opengl_core/core/x11_display.h"
#include "opengl_core/core/x11_event_mask.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "opengl_core/core/gl_functions.h"

namespace opengl_core
{
  struct render_system::render_system_impl
  {
    render_context m_context;
    render_window m_window;
    fb_config m_fbc;
    Atom m_delete_window;
  };

  render_system::render_system() :
    m_impl(new render_system_impl)
  {}

  render_system::~render_system()
  {
    delete m_impl;
  }

  bool render_system::init_system()
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

    m_impl->m_fbc.choose_best((*this));

    m_impl->m_window.init((*this), m_impl->m_fbc);
    Window &window = *static_cast<Window*>((m_impl->m_window.impl()));
    m_impl->m_window.map();
    m_impl->m_delete_window = XInternAtom(display, "WM_DELETE_WINDOW",
      False);
    if (!XSetWMProtocols(display, window, &m_impl->m_delete_window , 1)) {
      std::cerr << "Set Window Protocols Failed" << std::endl;
    }

    m_impl->m_context.init((*this), m_impl->m_window, m_impl->m_fbc);
    m_impl->m_context.make_current(m_impl->m_window);

    gl_functions::configure(m_impl->m_context);
    m_impl->m_context.make_not_current();

    render_loop();

    return true;
  }

  void render_system::render_loop()
  {
    bool terminate = false;
    bool exposed = false;
    XEvent x_event;
    while (!terminate) {
      while (::XPending(display)) {
        XNextEvent(display, &x_event);
        if (x_event.type == Expose) {
          exposed = true;
        }
        if (x_event.type == ClientMessage) {
          if ((Atom)x_event.xclient.data.l[0] == m_impl->m_delete_window) {
            terminate = true;
          }
        }
      }

      if (terminate || !exposed) {
        continue;
      }

      m_impl->m_context.make_current(m_impl->m_window);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(1.0, 0.0, 0.0, 1.0);
      glXSwapBuffers(display, window);
      m_impl->m_context.make_not_current();
    }
  }

  void render_system::destroy()
  {
    m_impl->m_context.make_not_current();
    m_impl->m_context.destroy();
    m_impl->m_window.destroy();
    m_impl->m_fbc.destroy();
    x11_display::release();
    std::cout << x11_display::use_count() << std::endl;
  }
}

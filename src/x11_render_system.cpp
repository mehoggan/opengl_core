#include <core/render_system.h>

#include <core/fb_config.h>
#include <core/x11_display.h>

#include <chrono>
#include <iostream>
#include <thread>

#include <X11/Xlib.h>
#include <GL/glx.h>

namespace opengl_core
{
  thread_local render_context render_system::s_context;
  thread_local render_window render_system::s_window;

  bool render_system::init(const int requested_major,
    const int requested_minor)
  {
    XInitThreads();

    Display *&display = opengl_core::x11_display::acquire();

    // Set to 0 because this would be the initial version.
    // Negagive numbers do not make since here.
    int glx_major = 0;
    int glx_minor = 0;
    if (!glXQueryVersion(display, &glx_major, &glx_minor)) {
      destroy();
      return false;
    } else {
      if (glx_major < requested_major) {
        destroy();
        return false;
      }
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

    fb_config fbc;
    fbc.choose_best();

    s_window.init(fbc);
    s_window.map();

    s_context.init(s_window, fbc, 2, 0);

    s_context.make_current(s_window);
  }

  void render_system::run(bool threaded)
  {
    if (threaded) {
    } else {
    }
  }

  void render_system::destroy()
  {
    s_context.make_not_current();
    s_context.destroy();
    s_window.destroy();
    x11_display::release();
  }
}

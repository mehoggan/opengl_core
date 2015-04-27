#include <core/render_system.h>

#include <core/fb_config.h>
#include <core/x11_display.h>

#include <iostream>

#include <X11/Xlib.h>
#include <GL/glx.h>

namespace opengl_core
{
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
    fbc.choose_best(glx_major, glx_minor);
  }

  void render_system::destroy()
  {
    x11_display::release();
  }
}

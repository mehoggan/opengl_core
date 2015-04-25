#include <core/render_system.h>

#include <core/x11_display.h>

#include <iostream>

#include <X11/Xlib.h>
#include <GL/glx.h>


namespace
{

}

namespace opengl_core
{
  bool render_system::init(const int requested_major,
    const int requested_minor)
  {
    int glx_major, glx_minor;

    Display *&display = opengl_core::x11_display::acquire();
    if (glXQueryVersion(display, &glx_major, &glx_minor)) {
      if (glx_major >= requested_major) {
        if (glx_minor >= requested_minor) {
          // Accoring to https://www.opengl.org/sdk/docs/man2/xhtml/glXIntro.xml
          // glxQueryVersion returns both client and server. However, according
          // to https://www.opengl.org/sdk/docs/man2/xhtml/glXQueryVersion.xml
          // it only returns the server version string.
          std::cout << "server glx version string " << glx_major << "." <<
            glx_minor << std::endl;
          std::cout << "client glx version string " << glx_major << "." <<
            glx_minor << std::endl;
          return true;
        }
      }
    } else {
      destroy();
      return false;
    }
  }

  void render_system::destroy()
  {
    x11_display::release();
  }
}

#include <core/render_system.h>

#include <core/x11_display.h>

#include <iostream>

#include <X11/Xlib.h>
#include <GL/glx.h>


namespace
{
  thread_local int g_glx_major;
  thread_local int g_glx_minor;

  thread_local Display *&g_display = opengl_core::x11_display::acquire();
}

namespace opengl_core
{
  bool render_system::init(const int major, const int minor)
  {
    if (glXQueryVersion(g_display, &g_glx_major, &g_glx_minor)) {
      if (g_glx_major >= major) {
        if (g_glx_minor >= minor) {
          // Accoring to https://www.opengl.org/sdk/docs/man2/xhtml/glXIntro.xml
          // glxQueryVersion returns both client and server. However, according
          // to https://www.opengl.org/sdk/docs/man2/xhtml/glXQueryVersion.xml
          // it only returns the server version string.
          std::cout << "server glx version string " << g_glx_major << "." <<
            g_glx_minor << std::endl;
          std::cout << "client glx version string " << g_glx_major << "." <<
            g_glx_minor << std::endl;
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

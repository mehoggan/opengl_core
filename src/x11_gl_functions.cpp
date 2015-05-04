#include <core/gl_functions.h>

#include <core/x11_display.h>

#include <cassert>
#include <iostream>

#include <GL/glx.h>

PFNGLGETSTRINGIPROC glGetStringi = 0;

namespace opengl_core
{
  void arb_bootstrap(const render_context &context)
  {
    std::cout << "Running OpenGL Core Booststrap with ARB" << std::endl;

    if (context.query_major_version() >= 3) {
      std::cout << "Finding extensions for " << context.query_major_version()
        << "." << context.query_minor_version() << std::endl;

      glGetStringi = (PFNGLGETSTRINGIPROC)glXGetProcAddressARB(
        (GLubyte *)"glGetStringi");
      assert(glGetStringi && "Could not acquire glGetStringi");

      GLint n = 0;
      glGetIntegerv(GL_NUM_EXTENSIONS, &n);
      for (GLint i = 0; i < n; ++i) {
        const char* extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
        printf("Ext %d: %s\n", i, extension);
      }
    } else {
      std::cout << "Finding extensions for " << context.query_major_version()
        << "." << context.query_minor_version() << std::endl;
    }
  }

  void bootstrap(const render_context &context)
  {
    std::cout << "Running OpenGL Core Booststrap" << std::endl;

    const GLubyte *extensions = glGetString(GL_EXTENSIONS);
    std::cout << "GL_EXTENSIONS String = " << extensions << std::endl;
  }

  void configure_gl_functions(const render_context &context)
  {
    Display *&display = x11_display::acquire();
    const int screen = DefaultScreen(display);

    const char *glx_exts = glXQueryExtensionsString(display, screen);
    if (is_extension_supported(glx_exts, "GLX_ARB_get_proc_address")) {
      arb_bootstrap(context);
    } else {
      bootstrap(context);
    }

    x11_display::release();
  }
}

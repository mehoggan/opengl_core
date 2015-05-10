#include <core/gl_functions.h>

#include <core/x11_display.h>

#include <cassert>
#include <iostream>
#include <sstream>

#include <GL/glx.h>

PFNGLGETSTRINGIPROC glGetStringi = 0;

namespace opengl_core
{
  thread_local extension_registry gl_functions::s_registry;

  void gl_functions::arb_bootstrap(const render_context &context)
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
        if (!s_registry.has_extension_loaded(extension)) {
          assert(s_registry.load_extension(extension));
        }
      }
    } else {
      std::cout << "Finding extensions for " << context.query_major_version()
        << "." << context.query_minor_version() << std::endl;
      const GLubyte *extensions = glGetString(GL_EXTENSIONS);

      std::stringstream ss((const char*)extensions);
      while (ss.good()) {
        std::string extension;
        std::getline(ss, extension, ',');
        if (!s_registry.has_extension_loaded(extension.c_str())) {
          assert(s_registry.load_extension(extension.c_str()));
        }
      }
    }
  }

  void gl_functions::bootstrap(const render_context &context)
  {
    std::cout << "Running OpenGL Core Booststrap" << std::endl;

    const GLubyte *extensions = glGetString(GL_EXTENSIONS);
    std::stringstream ss((const char*)extensions);
    while (ss.good()) {
      std::string extension;
      std::getline(ss, extension, ',');
      if (!s_registry.has_extension_loaded(extension.c_str())) {
        assert(s_registry.load_extension(extension.c_str()));
      }
    }
  }

  void gl_functions::configure(const render_context &context)
  {
    Display *&display = x11_display::acquire();
    const int screen = DefaultScreen(display);

    s_registry.init();

    const char *glx_exts = glXQueryExtensionsString(display, screen);
    if (is_extension_supported(glx_exts, "GLX_ARB_get_proc_address")) {
      arb_bootstrap(context);
    } else {
      bootstrap(context);
    }

    x11_display::release();
  }
}

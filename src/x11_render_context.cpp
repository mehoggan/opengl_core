#include <core/render_context.h>

#include <core/extension_checker.h>

#include <core/x11_display.h>

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <utility>

#include <X11/Xlib.h>
#include <GL/glx.h>

#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092

namespace
{
  typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*,
    GLXFBConfig, GLXContext, Bool, const int*);

  bool context_error = false;
  int context_error_handler(Display *, XErrorEvent *)
  {
    context_error = true;
  }
}

namespace opengl_core
{
  struct render_context::context_impl
  {
    GLXContext m_context;

    context_impl() :
      m_context(0)
    {}
  };

  render_context::render_context() :
    m_impl(new render_context::context_impl)
  {}

  render_context::~render_context()
  {}

  void render_context::init(render_window &window, fb_config &fbc,
    const int major, const int minor)
  {
    Display *&display = x11_display::acquire();
    GLXFBConfig &config = *(static_cast<GLXFBConfig*>(fbc.impl()));

    // Set to 0 because this would be the initial version.
    // Negagive numbers do not make since here.
    int glx_default_major = 0;
    int glx_default_minor = 0;
    if (!glXQueryVersion(display, &glx_default_major, &glx_default_minor)) {
      x11_display::release();
      assert(false && "No default version of GLX detected on HOST");
    }

    const int screen = DefaultScreen(display);
    const char *glx_exts = glXQueryExtensionsString(display, screen);

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB =
      (glXCreateContextAttribsARBProc)glXGetProcAddressARB(
        (const GLubyte *)"glXCreateContextAttribsARB");

    if (!is_extension_supported(glx_exts, "GLX_ARB_create_context" ) ||
      !glXCreateContextAttribsARB) {
      if (major <= glx_default_major && minor <= glx_default_minor) {
        x11_display::release();
        assert(false && "No possible way to create a context provided input.");
      } else {
        std::cerr << "Returning default context" << std::endl;
        m_impl->m_context = glXCreateNewContext(display, config, GLX_RGBA_TYPE,
          NULL, True); // NULL -> No Sharing of Context
        assert(m_impl->m_context && "Failed to create default context.");
      }
    } else {
      XLockDisplay(display);
      int (*oldHandler)(Display*, XErrorEvent*) = XSetErrorHandler(
        &context_error_handler);
      XUnlockDisplay(display);

      int context_attribs[] =
      {
        GLX_CONTEXT_MAJOR_VERSION_ARB, major,
        GLX_CONTEXT_MINOR_VERSION_ARB, minor,
        None
      };
      m_impl->m_context = glXCreateContextAttribsARB(display, config, NULL,
        True, context_attribs); // NULL -> No Sharing of Context

      // Sync to ensure any errors generated are processed.
      XSync(display, False);
      if (!context_error && m_impl->m_context) {
        std::cout << "Created a " << major << "." << minor << " GL Context."
          << std::endl;
      } else {
        // Couldn't create requeted context.  Fall back to old-style 2.x
        // context. When a context version below what is requested,
        // implementations will return the newest context version compatible
        // with OpenGL versions less than version requested.
        context_attribs[1] = 1;
        context_attribs[3] = 0;
        context_error = false;
        std::cerr << "Created a old-style GLX Context." << std::endl;
        m_impl->m_context = glXCreateContextAttribsARB(display, config, NULL,
          True, context_attribs); // NULL -> No Sharing of Context
      }

      if (!glXIsDirect(display, m_impl->m_context)) {
        std::cout << "Indirect GLX rendering context obtained." << std::endl;
      } else {
        std::cout << "Direct GLX rendering context obtained." << std::endl;
      }
    }

    x11_display::release();
  }

  void render_context::make_current(render_window &window)
  {
    Display *&display = x11_display::acquire();
    Window &win = *(static_cast<Window*>(window.impl()));
    glXMakeCurrent(display, win, m_impl->m_context);
    x11_display::release();
  }

  void render_context::make_not_current()
  {
    Display *&display = x11_display::acquire();
    glXMakeCurrent(display, 0, 0);
    x11_display::release();
  }

  void render_context::destroy()
  {
    if (m_impl->m_context) {
      Display *&display = x11_display::acquire();
      glXDestroyContext(display, m_impl->m_context);
      x11_display::release();
    }
  }

  void *render_context::impl()
  {
  }
}

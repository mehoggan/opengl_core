#include <core/render_context.h>

#include <core/extension_checker.h>
#include <core/render_system.h>
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
    GLint m_major;
    GLint m_minor;

    context_impl() :
      m_context(0),
      m_major(-1),
      m_minor(-1)
    {}
  };

  render_context::render_context() :
    m_impl(new render_context::context_impl)
  {}

  render_context::~render_context()
  {
    delete m_impl;
  }

  void render_context::init(render_system &, render_window &window,
    fb_config &fbc)
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

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = NULL;
    if (is_extension_supported(glx_exts, "GLX_ARB_get_proc_address")) {
      std::cout << "Using glXGetProcAddressARB" << std::endl;
      glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
        glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");
    } else {
      std::cout << "Using glXGetProcAddress" << std::endl;
      glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
        glXGetProcAddress((const GLubyte *)"glXCreateContextAttribsARB");
    }

    if (!is_extension_supported(glx_exts, "GLX_ARB_create_context" ) ||
      !glXCreateContextAttribsARB) {

      std::cerr << "Returning default context" << std::endl;
      m_impl->m_context = glXCreateNewContext(display, config, GLX_RGBA_TYPE,
        NULL, True); // NULL -> No Sharing of Context
      assert(m_impl->m_context && "Failed to create default context.");

    } else {
      XLockDisplay(display);
      int (*oldHandler)(Display*, XErrorEvent*) = XSetErrorHandler(
        &context_error_handler);
      XUnlockDisplay(display);

      GLint versions[][2] = {
        {4, 5}, {4, 4}, {4, 3}, {4, 2}, {4, 1}, {4, 0},
        {3, 3}, {3, 2}, {3, 1}, {3, 0},
        {2, 1}, {2, 0},
        {1, 5}, {1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0}};

      unsigned int count = sizeof(versions) / (2 * sizeof(GLint));
      unsigned int i = 0;
      for (; i < count; ++i) {
        GLint major = versions[i][0];
        GLint minor = versions[i][1];

        std::cout << "Trying to acquire OpenGL " << major << "." << minor
          << " versioned context" << std::endl;

        int context_attribs[] =
        {
          GLX_CONTEXT_MAJOR_VERSION_ARB, major,
          GLX_CONTEXT_MINOR_VERSION_ARB, minor,
          None
        };

        m_impl->m_context = glXCreateContextAttribsARB(display, config, NULL,
          True, context_attribs); // NULL -> No Sharing of Context

        XSync(display, False);

        if (!context_error && m_impl->m_context) {
          std::cout << "Created a " << major << "." << minor << " GL Context."
            << std::endl;
          m_impl->m_major = major;
          m_impl->m_minor = minor;
          break;
        } else {
          context_error = false;
        }
      }

      if (i != count) {
        if (!glXIsDirect(display, m_impl->m_context)) {
          std::cout << "Indirect GLX rendering context obtained." << std::endl;
        } else {
          std::cout << "Direct GLX rendering context obtained." << std::endl;
        }
      } else {
        std::cerr << "Failed to create context" << std::endl;
        assert(false && "Failed to create context");
      }
    }

    x11_display::release();
  }

  void render_context::make_current(render_window &window)
  {
    Display *&display = x11_display::acquire();
    Window &win = *(static_cast<Window*>(window.impl()));
    assert(glXMakeCurrent(display, win, m_impl->m_context) &&
      "Failed to make context current");
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
    return (void*)(&(m_impl->m_context));
  }

  int render_context::query_major_version() const
  {
    return m_impl->m_major;
  }

  int render_context::query_minor_version() const
  {
    return m_impl->m_minor;
  }
}

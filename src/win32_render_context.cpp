#include "core/render_context.h"

#include "core/extension_checker.h"
#include "core/render_system.h"
#include "core/symbol_loader.h"
#include "core/win32_error_handler.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

#include <Windows.h>
#include <GL/gl.h>
#include <GL/wglext.h>

namespace opengl_core
{
  struct render_context::context_impl
  {
    HGLRC m_context;
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

  void render_context::init(render_system &system, render_window &window,
    fb_config &fbc)
  {
    auto hwnd = *static_cast<HWND*>(window.impl());
    auto hdc = ::GetDC(hwnd);
    if (!hdc) {
      print_last_error_and_assert();
    }

    // You have to create a context to find out if ARB functions are available.
    // In order to create a context the HDC associated with a HWND must have a
    // a PIXELFORMATDESTRIPTOR associated with it.
    PIXELFORMATDESCRIPTOR tmp_pfd;
    memset(&tmp_pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    tmp_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    tmp_pfd.nVersion = 1;
    tmp_pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL |
      PFD_DRAW_TO_WINDOW;
    tmp_pfd.iPixelType = PFD_TYPE_RGBA;
    tmp_pfd.cColorBits = 32;
    tmp_pfd.cDepthBits = 24;
    tmp_pfd.iLayerType = PFD_MAIN_PLANE;
    int pixel_format = ::ChoosePixelFormat(hdc, &tmp_pfd);
    if (pixel_format == 0) {
      print_last_error_and_assert();
    }
    if (!::SetPixelFormat(hdc, pixel_format, &tmp_pfd)) {
      print_last_error_and_assert();
    }

    // We will now create a device context to access the extensions necessary
    // to create our actual context with the highest version possible for the
    // given hardware.
    HGLRC tmp_ctx = wglCreateContext(hdc);
    if (!tmp_ctx) {
      print_last_error_and_assert();
    }
    if (!wglMakeCurrent(hdc, tmp_ctx)) {
      wglDeleteContext(tmp_ctx);
      print_last_error_and_assert();
    }

    // Incase something fails below destroy() might have a chance.
    m_impl->m_context = tmp_ctx;

    // Windows brain boggler. Now that we have a context we can actually choose
    // the best PIXELFORMATDESTRIPTOR. fbc_config::choose_best() will destroy
    // the initial window and recreate it with the best fbc possible and assign
    // the fbc to the HDC associated with the newly created window.
    fbc.choose_best(system, &window);
    hwnd = *static_cast<HWND*>(window.impl());
    if (!hwnd) {
      print_last_error_and_assert();
    }
    hdc = ::GetDC(hwnd);
    if (!hdc) {
      print_last_error_and_assert();
    }

    // We need the wglGetExtensionsStringARB proc to check for the existence
    // of other extensions. If this fails there is no point of continuing on.
    typedef const char*(WINAPI *PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC);
    PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB = 0;
    wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)
      wglGetProcAddress("wglGetExtensionsStringARB");
    if (!wglGetExtensionsStringARB ||
      wglGetExtensionsStringARB == (void*)-1) {
      wglDeleteContext(tmp_ctx);
      print_last_error_and_assert();
    }
    const char *extensions = wglGetExtensionsStringARB(hdc);
    if (extensions == nullptr) {
      wglDeleteContext(tmp_ctx);
      print_last_error_and_assert();
    }

    // We want to know if the improved version of wglCreateContext exists
    // so we can create higher level contexts. If it does not exist then we
    // keep the previously created one around.
    HGLRC next_hglrc = nullptr;
    if (is_extension_supported(extensions, "WGL_ARB_create_context")) {
      typedef HGLRC(WINAPI *PFNGWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC,
        const int *);
      PFNGWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = 0;
      wglCreateContextAttribsARB = (PFNGWGLCREATECONTEXTATTRIBSARBPROC)
        wglGetProcAddress("wglCreateContextAttribsARB");
      if (!wglCreateContextAttribsARB ||
        wglCreateContextAttribsARB == (void*)-1) {
        wglDeleteContext(tmp_ctx);
        print_last_error_and_assert();
      }

      // As per https://www.opengl.org/wiki/History_of_OpenGL these are
      // the supported version numbers. We can only create contexts
      // associated with the versions in this table.
      GLint versions[][2] = {
        { 4, 5 }, { 4, 4 }, { 4, 3 }, { 4, 2 }, { 4, 1 }, { 4, 0 },
        { 3, 3 }, { 3, 2 }, { 3, 1 }, { 3, 0 },
        { 2, 1 }, { 2, 0 },
        { 1, 5 }, { 1, 4 }, { 1, 3 }, { 1, 2 }, { 1, 1 }, { 1, 0 } };

      for (auto version : versions) {
        GLint major = version[0];
        GLint minor = version[1];

        int attribs[] =
        {
          WGL_CONTEXT_MAJOR_VERSION_ARB, major,
          WGL_CONTEXT_MINOR_VERSION_ARB, minor,
          WGL_CONTEXT_FLAGS_ARB, 0,
          0
        };

        next_hglrc = wglCreateContextAttribsARB(hdc, nullptr, attribs);

        // Its okay to fail creation if hardware does not support major.minor
        // versions of the device context. Just continue to the next version.
        // Other wise parse the version number and verify it aligns with the
        // current major.minor. If all these conditions are met break the loop.
        if (!next_hglrc) {
          print_last_error();
        } else {
          const GLubyte *version = glGetString(GL_VERSION);
          std::string gl_check_str((const char*)version);
          std::stringstream ss;
          ss << major << '.' << minor;
          std::string check_str = ss.str();
          size_t substr_index = gl_check_str.find(check_str);
          if (substr_index != std::string::npos) {
            std::string check;
            m_impl->m_context = next_hglrc;
            m_impl->m_major = major;
            m_impl->m_minor = minor;
            wglMakeCurrent(nullptr, nullptr);
            if (!wglDeleteContext(tmp_ctx)) {
              print_last_error(); // Potential memory leak. But not critical
            }
            break;
          }
        }
      }
    }

    // There are two cases where this will be true. One the extension
    // WGL_ARB_create_context is not supported or the loop above could
    // not find an appropriate version'd context.
    if (next_hglrc == nullptr) {
      m_impl->m_context = tmp_ctx;
      const GLubyte *version = glGetString(GL_VERSION);
      size_t len = strlen((const char*)version);
      for (size_t i = 0; i < len; ++i) {
        if (version[i] == '.') {
          m_impl->m_major = (GLint)(version[i - 1] - '0');
          m_impl->m_minor = (GLint)(version[i + 1] - '0');
        }
      }
      make_not_current();
    }
  }

  void render_context::make_current(render_window &window)
  {
    auto hwnd = *static_cast<HWND*>(window.impl());
    auto hdc = ::GetDC(hwnd);
    if (!hdc) {
      print_last_error();
    }
    if (!wglMakeCurrent(hdc, m_impl->m_context)) {
      print_last_error();
    }
  }

  void render_context::make_not_current()
  {
    wglMakeCurrent(nullptr, nullptr);
  }

  void render_context::destroy()
  {
    if (m_impl->m_context) {
      if (!wglDeleteContext(m_impl->m_context)) {
        print_last_error();
      }
    }
  }

  void *render_context::impl()
  {
    return (void*)m_impl->m_context;
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

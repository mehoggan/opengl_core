#include <core/fb_config.h>

#include <core/extension_checker.h>
#include <core/symbol_loader.h>
#include <core/render_window.h>
#include <core/win32_error_handler.h>

#include <cassert>
#include <cstring>
#include <limits>
#include <iomanip>
#include <iostream>

#include <Windows.h>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>

namespace
{
  const int fb_attrib[] = {
    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
    WGL_SWAP_METHOD_ARB, WGL_SWAP_EXCHANGE_ARB,
    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 24,
    WGL_STENCIL_BITS_ARB, 8,
    0
  };
}

namespace opengl_core
{
  struct fb_config::fb_config_impl
  {
    PIXELFORMATDESCRIPTOR m_best_config;

    fb_config_impl()
    {
      memset(&m_best_config, 0, sizeof(PIXELFORMATDESCRIPTOR));
    }
  };

  fb_config::fb_config() :
    m_impl(new fb_config::fb_config_impl)
  {}

  fb_config::~fb_config()
  {
    delete m_impl;
  }

  void fb_config::choose_best(render_window *detail)
  {
    if (!detail) {
      // This is a forced error so make sure not to show a false positive.
      ::SetLastError(0);
      print_last_error_and_assert();
    }

    // This will destroy the default window created in the ctor. This is called
    // by the render context because it must be created first before
    // the best PIXEL FORMAT can be chosen.
    detail->init(*this);
    detail->map();

    HWND hwnd = *reinterpret_cast<HWND*>(detail->impl());
    if (!hwnd) {
      // This is a forced error so make sure not to show a false positive.
      ::SetLastError(0);
      print_last_error_and_assert();
    }

    HDC hdc = ::GetDC(hwnd);
    if (!hdc) {
      print_last_error_and_assert();
    }

    typedef const char*(WINAPI *PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC);
    PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB = 0;
    wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)
      wglGetProcAddress("wglGetExtensionsStringARB");
    if (!wglGetExtensionsStringARB ||
      wglGetExtensionsStringARB == (void*)(-1)) {
      print_last_error_and_assert();
    }

    const char *extensions = wglGetExtensionsStringARB(hdc);
    if (is_extension_supported(extensions, "WGL_ARB_pixel_format")) {
      typedef BOOL (*PFNWGLCHOOSEPIXELFORMATARB)(HDC, const int *,
        const FLOAT *, UINT, int, UINT);
      PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = 0;
      wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)
        wglGetProcAddress("wglChoosePixelFormatARB");
      if (!wglChoosePixelFormatARB) {
        print_last_error_and_assert();
      }

      int pixel_format;
      UINT num_formats = 0;
      if (!wglChoosePixelFormatARB(hdc, fb_attrib, NULL, 1, &pixel_format,
        &num_formats) || num_formats == 0) {
        print_last_error_and_assert();
      }

      PIXELFORMATDESCRIPTOR pfd;
      int pixel_format_index = ::DescribePixelFormat(hdc, pixel_format,
        sizeof(PIXELFORMATDESCRIPTOR), &pfd);
      if (pixel_format_index == 0) {
        print_last_error_and_assert();
      }

      m_impl->m_best_config = pfd;
      if (!::SetPixelFormat(hdc, pixel_format, &m_impl->m_best_config)) {
        print_last_error_and_assert();
      }
    }
  }

  void *fb_config::impl()
  {
    return (void*)(&(m_impl->m_best_config));
  }
}

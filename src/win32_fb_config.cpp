#include <core/fb_config.h>

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
    assert(detail && "Win32 Requires render_window to create Frame"
      " Buffer Config");

    HWND hwnd = *reinterpret_cast<HWND*>(detail->impl());
    assert(hwnd && "Window creation must have failed somehow");

    HDC hdc = ::GetDC(hwnd);
    if (!hdc) {
      print_last_error_and_assert();
    }

    symbol_loader library("OpenGL32.dll");
    assert(library.get_good() && "Failed to load OpenGL library");

    // For 3.0 Version Contexts (Which we don't have)
    typedef const char* (WINAPI *PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);
    PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB = 0;
    wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)
      wglGetProcAddress("wglGetExtensionsStringARB");
    if (wglGetExtensionsStringARB == 0 ||
      (wglGetExtensionsStringARB == (void*)0x1) ||
      (wglGetExtensionsStringARB == (void*)0x2) ||
      (wglGetExtensionsStringARB == (void*)0x3) ||
      (wglGetExtensionsStringARB == (void*)-1)) {

      wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)library.load(
        "wglGetExtensionsStringARB");
    }

    // If 3.0 Version above fails try this
    typedef const char* (WINAPI *PFNWGLGETEXTENSIONSSTRINGEXTPROC)(void);
    PFNWGLGETEXTENSIONSSTRINGEXTPROC wglGetExtensionsStringEXT = 0;
    wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)
      wglGetProcAddress("wglGetExtensionsStringEXT");
    if (wglGetExtensionsStringEXT == 0 ||
      (wglGetExtensionsStringEXT == (void*)0x1) ||
      (wglGetExtensionsStringEXT == (void*)0x2) ||
      (wglGetExtensionsStringEXT == (void*)0x3) ||
      (wglGetExtensionsStringEXT == (void*)-1)) {

      wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)library.load(
        "wglGetExtensionsStringEXT");
    }
  }

  void *fb_config::impl()
  {
    return (void*)(&(m_impl->m_best_config));
  }
}

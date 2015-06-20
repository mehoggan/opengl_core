#include <core/render_system.h>

#include <core/fb_config.h>
#include <core/gl_functions.h>
#include <core/render_context.h>
#include <core/render_window.h>
#include <core/win32_error_handler.h>

#include <chrono>
#include <iostream>
#include <thread>

#include <Windows.h>

namespace opengl_core
{
  struct render_system::render_system_impl
  {
    render_context m_context;
    render_window m_window;
    fb_config m_fbc;
  };

  render_system::render_system() :
    m_impl(new render_system_impl)
  {}

  render_system::~render_system()
  {
    delete m_impl;
  }

  bool render_system::init()
  {
    // This function will destroy the mapped window and then recreate it
    // with a new frame buffer config.
    m_impl->m_context.init(m_impl->m_window, m_impl->m_fbc);
    m_impl->m_context.make_current(m_impl->m_window);
    m_impl->m_window.map();

    gl_functions::configure(m_impl->m_context);
    m_impl->m_context.make_not_current();

    MSG msg;
    memset(&msg, 0, sizeof(msg));
    unsigned int quit_message_count = 0;
    auto hwnd = *static_cast<HWND*>(m_impl->m_window.impl());
    while (true) {
      if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        if (msg.message == WM_QUIT) {
          if (quit_message_count >= 1) {
            break;
          }
          quit_message_count++;
        }
      } else {
        m_impl->m_context.make_current(m_impl->m_window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 0.0, 0.0, 1.0);
        auto hdc = ::GetDC(hwnd);
        SwapBuffers(hdc);
        m_impl->m_context.make_not_current();
      }
    }

    return true;
  }

  void render_system::destroy()
  {
    m_impl->m_context.make_not_current();
    m_impl->m_context.destroy();
    m_impl->m_window.destroy();
  }
}

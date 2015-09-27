#include "core/render_system.h"

#include "core/concurrent_queue.h"
#include "core/fb_config.h"
#include "core/gl_functions.h"
#include "core/render_context.h"
#include "core/render_window.h"
#include "core/win32_error_handler.h"

#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

#include <Windows.h>

namespace opengl_core
{
  struct render_system::render_system_impl
  {
    render_context m_context;
    render_window m_window;
    fb_config m_fbc;

    std::mutex m_render_mutex;
    bool m_render;

    render_system_impl() :
      m_render(true)
    {}
  };

  render_system::render_system() :
    m_impl(new render_system_impl)
  {}

  render_system::~render_system()
  {
    delete m_impl;
  }

  void render_system::render_loop()
  {
    bool render = true;
    auto hwnd = *static_cast<HWND*>(m_impl->m_window.impl());
    auto hdc = ::GetDC(hwnd);
    do {
      {
        std::lock_guard<std::mutex> lock(m_impl->m_render_mutex);
        render = m_impl->m_render;
      }

      if (render && IsWindow(hwnd)) {
        m_impl->m_context.make_current(m_impl->m_window);
        {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glClearColor(1.0, 0.0, 0.0, 1.0);
          SwapBuffers(hdc);
        }
        m_impl->m_context.make_not_current();
      }
    } while (render);
  }

  bool render_system::init()
  {
    // This function will destroy the mapped window and then recreate it
    // with a new frame buffer config.
    m_impl->m_context.init(*this, m_impl->m_window, m_impl->m_fbc);
    m_impl->m_context.make_current(m_impl->m_window);
    m_impl->m_window.map();

    gl_functions::configure(m_impl->m_context);
    m_impl->m_context.make_not_current();

    std::thread render_thread(std::bind(&render_system::render_loop,
      std::ref(*this)));

    MSG msg;
    memset(&msg, 0, sizeof(msg));
    auto hwnd = *static_cast<HWND*>(m_impl->m_window.impl());
    bool render = true;
    do {
      if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
      }

      // When the render_window's init function is called it provides
      // (*this) as meta for the window. When WM_DESTROY is received by
      { // message pump it calls render_system::terminate which ends this loop.
        std::lock_guard<std::mutex> lock(m_impl->m_render_mutex);
        render = m_impl->m_render;
      }
    } while (render);

    render_thread.join();

    return true;
  }

  void render_system::terminate()
  {
    std::lock_guard<std::mutex> lock(m_impl->m_render_mutex);
    m_impl->m_render = false;
  }

  void render_system::destroy()
  {
    m_impl->m_context.make_not_current();
    m_impl->m_context.destroy();
    m_impl->m_window.destroy();
  }
}

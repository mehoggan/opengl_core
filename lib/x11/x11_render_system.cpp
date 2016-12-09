#include "opengl_core/core/render_system.h"

#include "opengl_core/core/fb_config.h"
#include "opengl_core/core/render_context.h"
#include "opengl_core/core/x11/x11_display.h"
#include "opengl_core/core/x11/x11_event_mask.h"

#include <cassert>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

#include "opengl_core/core/gl_functions.h"

#include <GL/glx.h>

namespace opengl_core
{
  struct render_system::render_system_impl
  {
    render_context m_context;
    render_window m_window;
    fb_config m_fbc;
    render_function m_renderer;
    bool m_threaded;
    std::atomic_bool m_spin_lock;
    std::atomic_bool m_render;

    Atom m_delete_window;
  };

  static void threaded_render_loop(render_system &render)
  {
    render_system::render_system_impl *impl =
      reinterpret_cast<render_system::render_system_impl *>(render.impl());

    Display *&display = opengl_core::x11_display::acquire();
    Window &window = *static_cast<Window*>(impl->m_window.impl());

    impl->m_context.destroy();
    impl->m_context.init_render_context(render, impl->m_window, impl->m_fbc);
    impl->m_context.make_current(impl->m_window);

    impl->m_spin_lock.store(false, std::memory_order_release);

    bool render_flag = false;
    while (!impl->m_render.compare_exchange_weak(render_flag, true,
      std::memory_order_acquire)) {
      render_flag = false;

      impl->m_context.make_current(impl->m_window);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(1.0, 0.0, 0.0, 1.0);
      impl->m_renderer(0);
      glXSwapBuffers(display, window);
      impl->m_renderer(0);
      std::cout << "Drawing" << std::endl << std::flush;
      impl->m_context.make_not_current();
    }
    opengl_core::x11_display::release();
  }

  render_system::render_system(render_function &render, bool threaded) :
    m_impl(new render_system_impl)
  {
    m_impl->m_renderer = render;
    m_impl->m_threaded = threaded;
    m_impl->m_spin_lock.store(true, std::memory_order_relaxed);
    m_impl->m_render.store(true, std::memory_order_relaxed);
  }

  render_system::~render_system()
  {
    delete m_impl;
  }

  static void event_render_loop(render_system &system)
  {
    Display *&display = opengl_core::x11_display::acquire();
    render_system::render_system_impl *impl =
        reinterpret_cast<render_system::render_system_impl *>(system.impl());
    Window &window = *static_cast<Window*>(impl->m_window.impl());

    bool terminate = false;
    bool exposed = false;
    XEvent x_event;
    while (!terminate) {
      int n = XEventsQueued(display, QueuedAfterReading);
      while (n--) {
        XNextEvent(display, &x_event);
        if (x_event.type == Expose) {
          exposed = true;
        } else if (x_event.type == ClientMessage) {
          if ((Atom)x_event.xclient.data.l[0] == impl->m_delete_window) {
            terminate = true;
          }
        }
      }

      if (terminate || !exposed) {
        continue;
      }

      impl->m_context.make_current(impl->m_window);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(1.0, 0.0, 0.0, 1.0);
      impl->m_renderer(0);
      glXSwapBuffers(display, window);
      impl->m_context.make_not_current();
    }

    x11_display::release();
  }

  static void event_loop(render_system &system)
  {
    Display *&display = opengl_core::x11_display::acquire();
    render_system::render_system_impl *impl =
        reinterpret_cast<render_system::render_system_impl *>(system.impl());

    bool terminate = false;
    bool exposed = false;
    XEvent x_event;
    while (!terminate) {
      int n = XEventsQueued(display, QueuedAfterReading);
      while (n--) {
        XNextEvent(display, &x_event);
        if (x_event.type == Expose) {
          exposed = true;
        } else if (x_event.type == ClientMessage) {
          if ((Atom)x_event.xclient.data.l[0] == impl->m_delete_window) {
            impl->m_render.store(false, std::memory_order_release);
            terminate = true;
          }
        }
      }

      if (terminate || !exposed) {
        continue;
      }
    }

    x11_display::release();
  }


  bool render_system::init_system()
  {
    XInitThreads();

    Display *&display = opengl_core::x11_display::acquire();

    // Set to 0 because this would be the initial version.
    // Negagive numbers do not make since here.
    int glx_major = 0;
    int glx_minor = 0;
    if (!glXQueryVersion(display, &glx_major, &glx_minor)) {
      std::cerr << "Failed to query glx version" << std::endl;
      destroy();
      return false;
    }

    // According to https://www.opengl.org/sdk/docs/man2/xhtml/
    // glXIntro.xml glxQueryVersion returns both client and server.
    // However, according // to https://www.opengl.org/sdk/docs/man2/
    // xhtml/glXQueryVersion.xml it only returns the server version
    // string.
    std::cout << "server glx version string " << glx_major << "." <<
      glx_minor << std::endl;
    std::cout << "client glx version string " << glx_major << "." <<
      glx_minor << std::endl;

    m_impl->m_fbc.choose_best((*this));

    m_impl->m_window.init_window((*this), m_impl->m_fbc);
    Window &window = *static_cast<Window*>((m_impl->m_window.impl()));
    m_impl->m_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
    if (!XSetWMProtocols(display, window, &m_impl->m_delete_window, 1)) {
      std::cout << "Set Window Protocols Failed" << std::endl;
    }
    m_impl->m_window.map();

    m_impl->m_context.init_render_context((*this), m_impl->m_window,
      m_impl->m_fbc);
    m_impl->m_context.make_current(m_impl->m_window);

    gl_functions::configure(m_impl->m_context);
    m_impl->m_context.make_not_current();

    if (!m_impl->m_threaded) {
      event_render_loop((*this));
    } else {
      std::thread render_thread(std::bind(&threaded_render_loop,
        std::ref(*this)));
      bool spin = false;
      while(!m_impl->m_spin_lock.compare_exchange_weak(spin, true,
        std::memory_order_acquire)) {
        spin = false;
      }
      event_loop((*this));
      if (render_thread.joinable()) {
        render_thread.join();
      }
    }

    x11_display::release();

    return true;
  }

  void render_system::terminate_system()
  {
  }

  void render_system::destroy()
  {
    m_impl->m_context.make_not_current();
    m_impl->m_context.destroy();
    m_impl->m_window.destroy();
    m_impl->m_fbc.destroy();
    x11_display::release();
    std::cout << x11_display::use_count() << std::endl;
  }

  void *render_system::impl()
  {
    return (void*)m_impl;
  }
}

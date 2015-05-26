#include <core/render_system.h>

#include <core/fb_config.h>
#include <core/gl_functions.h>
#include <core/render_context.h>
#include <core/render_window.h>

#include <chrono>
#include <iostream>
#include <thread>

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

    return true;
  }

  void render_system::run(bool threaded)
  {

    if (threaded) {

    } else {

    }
  }

  void render_system::destroy()
  {
    m_impl->m_context.make_not_current();
    m_impl->m_context.destroy();
    m_impl->m_window.destroy();
  }
}

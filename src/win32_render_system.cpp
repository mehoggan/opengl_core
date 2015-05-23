#include <core/render_system.h>

#include <core/fb_config.h>
#include <core/gl_functions.h>

#include <chrono>
#include <iostream>
#include <thread>

namespace opengl_core
{
  bool render_system::init()
  {
    m_window.map();
    m_fbc.choose_best(&m_window);

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
    m_context.make_not_current();
    m_context.destroy();
    m_window.destroy();
  }
}

#ifndef RENDER_WINDOW_H_INCLUDED
#define RENDER_WINDOW_H_INCLUDED

#include "opengl_core/core/non_copyable.h"

#include "opengl_core/core/fb_config.h"

#include <memory>

namespace opengl_core
{
  class render_system;

  class render_window : public non_copyable
  {
  private:
    struct window_impl;
    window_impl *m_impl;

  public:
    render_window();
    ~render_window();

    void init(render_system &system, fb_config &fbc);
    void map();
    void destroy();

    void *impl();
  };
}

#endif

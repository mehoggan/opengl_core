#ifndef RENDER_WINDOW_H_INCLUDED
#define RENDER_WINDOW_H_INCLUDED

#include <declspec.h>

#include <core/fb_config.h>
#include <core/non_copyable.h>

#include <memory>

namespace opengl_core
{
  class render_window : public non_copyable
  {
  private:
    struct window_impl;
    std::shared_ptr<window_impl> m_impl;

  public:
    render_window();
    ~render_window();

    void init(fb_config &fbc);
    void map();
    void destroy();

    void *impl();
  };
}

#endif

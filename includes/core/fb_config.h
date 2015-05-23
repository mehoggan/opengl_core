#ifndef FB_CONFIG_H_INCLUDED
#define FB_CONFIG_H_INCLUDED

#include <declspec.h>

#include <core/non_copyable.h>

#include <memory>

namespace opengl_core
{
  class render_window;

  class OPENGL_CORE_API fb_config : public non_copyable
  {
  private:
    struct fb_config_impl;
    fb_config_impl *m_impl;

  public:
    fb_config();
    ~fb_config();

    void choose_best(render_window *detail = nullptr);

    void *impl();
  };
}

#endif

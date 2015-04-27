#ifndef FB_CONFIG_H_INCLUDED
#define FB_CONFIG_H_INCLUDED

#include <declspec.h>

#include <memory>

namespace opengl_core
{
  class OPENGL_CORE_API fb_config
  {
  private:
    struct fb_config_impl;
    std::shared_ptr<fb_config_impl> m_impl;

  public:
    fb_config();
    ~fb_config();

    void choose_best();

    void *impl();
  };
}

#endif

#ifndef RENDER_SYSTEM_H_INCLUDED
#define RENDER_SYSTEM_H_INCLUDED

#include "declspec.h"

#include "opengl_core/core/non_copyable.h"

namespace opengl_core
{
  class OPENGL_CORE_API render_system : public non_copyable
  {
  private:
    struct render_system_impl;
    render_system_impl *m_impl;

  private:
    void render_loop();

  public:
    render_system();
    ~render_system();

    bool init();
    void terminate();
    void destroy();
  };
}

#endif

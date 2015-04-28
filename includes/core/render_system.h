#ifndef RENDER_SYSTEM_H_INCLUDED
#define RENDER_SYSTEM_H_INCLUDED

#include <declspec.h>

#include <core/render_context.h>
#include <core/render_window.h>

namespace opengl_core
{
  class OPENGL_CORE_API render_system
  {
  private:
    static thread_local render_context s_context;
    static thread_local render_window s_window;

  public:
    static thread_local bool init(const int requested_major,
      const int requested_minor);
    static thread_local void destroy();
  };
}

#endif

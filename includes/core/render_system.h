#ifndef RENDER_SYSTEM_H_INCLUDED
#define RENDER_SYSTEM_H_INCLUDED

#include <declspec.h>

#include <core/render_context.h>
#include <core/render_window.h>

// NOTE: thread_local on functions to my understanding is used to only denote
// that the function accesses a thread_local static variable.
namespace opengl_core
{
  class OPENGL_CORE_API render_system
  {
  private:
    static thread_local render_context s_context;
    static thread_local render_window s_window;

  public:
    static thread_local bool init();

    static thread_local void run(bool threaded = true);

    static thread_local void destroy();
  };
}

#endif

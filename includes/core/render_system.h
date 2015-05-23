#ifndef RENDER_SYSTEM_H_INCLUDED
#define RENDER_SYSTEM_H_INCLUDED

#include <declspec.h>

#include <core/non_copyable.h>
#include <core/render_context.h>
#include <core/render_window.h>

// NOTE: gl_thread_local on functions to my understanding is used to only denote
// that the function accesses a gl_thread_local static variable.
namespace opengl_core
{
  class OPENGL_CORE_API render_system : public non_copyable
  {
  private:
    render_context m_context;
    render_window m_window;
    fb_config m_fbc;

  public:
    bool init();
    void run(bool threaded = true);
    void destroy();
  };
}

#endif

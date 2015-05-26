#ifndef RENDER_SYSTEM_H_INCLUDED
#define RENDER_SYSTEM_H_INCLUDED

#include <declspec.h>

#include <core/non_copyable.h>

// NOTE: gl_thread_local on functions to my understanding is used to only denote
// that the function accesses a gl_thread_local static variable.
namespace opengl_core
{
  class OPENGL_CORE_API render_system : public non_copyable
  {
  private:
    struct render_system_impl;
    render_system_impl *m_impl;

  public:
    render_system();
    ~render_system();

    bool init();
    void run(bool threaded = true);
    void destroy();
  };
}

#endif

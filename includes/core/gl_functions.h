#ifndef GL_FUNCTIONS_H_INCLUDED
#define GL_FUNCTIONS_H_INCLUDED

#include <core/extension_registry.h>

namespace opengl_core
{
  /*! This struct's function should only be called while a context has been made
   *  current. The loading of extensions differs from platform to platform.
   *  It should also be noted that this function should be called by the thread
   *  who owns the context.
   */
  struct gl_functions
  {
  private:
    thread_local static extension_registry s_registry;

  private:
    thread_local static void arb_bootstrap(const render_context &context);
    thread_local static void bootstrap(const render_context &context);

  public:
    thread_local static void configure(const render_context &context);
  };
}

// For bootstrap purposes
extern PFNGLGETSTRINGIPROC glGetStringi;

#endif

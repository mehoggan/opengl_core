#ifndef GL_FUNCTIONS_H_INCLUDED
#define GL_FUNCTIONS_H_INCLUDED

#include <core/extension_checker.h>
#include <core/render_context.h>

#include <GL/gl.h>
#include <GL/glext.h>

namespace opengl_core
{
  /*! This function should only be called while a context has been made
   *  current. The loading of extensions differs from platform to platform.
   *  It should also be noted that this function should be called by the thread
   *  who owns the context.
   */
  extern "C" void configure_gl_functions(const render_context &context);
}

// For bootstrap purposes
extern PFNGLGETSTRINGIPROC glGetStringi;

#endif

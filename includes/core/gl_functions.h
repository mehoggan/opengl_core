#ifndef GL_FUNCTIONS_H_INCLUDED
#define GL_FUNCTIONS_H_INCLUDED

#include <declspec.h>

#include <core/extension_registry.h>
#include <core/render_context.h>
#include <core/symbol_loader.h>

#include <map>
#include <utility>
#include <vector>

namespace opengl_core
{
  /*! This struct's function should only be called while a context has been made
   *  current. The loading of extensions differs from platform to platform.
   *  It should also be noted that this struct's public static function should
   *  be called by the thread who owns the context.
   */
  struct gl_functions
  {
  private:
    static void load_1_2(symbol_loader *sym_loader);
    static void load_1_3(symbol_loader *sym_loader);
    static void load_1_4(symbol_loader *sym_loader);
    static void load_1_5(symbol_loader *sym_loader);
    static void load_2_0(symbol_loader *sym_loader);
    static void load_2_1(symbol_loader *sym_loader);
    static void load_3_0(symbol_loader *sym_loader);

  public:
    static void configure(const render_context &context);
  };
}

// For bootstrap purposes
extern PFNGLGETSTRINGIPROC glGetStringi;

#endif

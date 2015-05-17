#ifndef EXTENSION_CHECKER_H_INCLUDED
#define EXTENSION_CHECKER_H_INCLUDED

#include <declspec.h>

namespace opengl_core
{
  extern "C"
  {
    OPENGL_CORE_API bool is_extension_supported(const char *ext_list,
      const char *extension);
  }
}

#endif

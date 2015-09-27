#ifndef EXTENSION_CHECKER_H_INCLUDED
#define EXTENSION_CHECKER_H_INCLUDED

namespace opengl_core
{
  extern "C"
  {
    bool is_extension_supported(const char *ext_list, const char *extension);
  }
}

#endif

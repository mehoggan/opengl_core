#include "opengl_core/core/extension_checker.h"

#include <cstring>

namespace opengl_core
{
  bool is_extension_supported(const char *ext_list, const char *extension)
  {
    const char *start;
    const char *where, *terminator;

    // Extension names should not have spaces.
    where = strchr(extension, ' ');
    if (where || *extension == '\0') {
      return false;
    }

    /* It takes a bit of care to be fool-proof about parsing the
     * OpenGL extensions string. Don't be fooled by sub-strings,
     * etc.
     */
    for (start = ext_list;;) {
      where = strstr(start, extension);

      if (!where) {
        break;
      }

      terminator = where + strlen(extension);

      if (where == start || *(where - 1) == ' ') {
        if (*terminator == ' ' || *terminator == '\0') {
          return true;
        }
      }

      start = terminator;
    }

    return false;
  }
}

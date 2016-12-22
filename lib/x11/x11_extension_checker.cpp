/* Copyright (C)
 *
 * Copyright 2013 Matthew Everett Hoggan
 *
 * Licensed under the Apache License, Version 2.0 (the "License")
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writting, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "opengl_core/core/x11/x11_extension_checker.h"

#include <cstring>

namespace opengl_core
{
  extern "C"
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
}

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
#include "opengl_core/core/init.h"

#include "opengl_core/core/x11/x11_display.h"

#include <X11/Xlib.h>

namespace opengl_core
{
  bool init()
  {
    bool ret = true;
    Status status = 0;

    status = XInitThreads();
    if (status == 0) {
      ret = false;
    }

    if (ret) {
      ret = x11_display_init();
    }

    return ret;
  }

  bool shutdown()
  {
    bool ret = true;

    return ret;
  }
}


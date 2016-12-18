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
#include "opengl_core/core/draw_buffer_config.h"

#include "opengl_core/core/x11/x11_display.h"

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace opengl_core
{
  static int visual_attribs[] =
  {
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_DOUBLEBUFFER, true,
    GLX_RED_SIZE, 1,
    GLX_GREEN_SIZE, 1,
    GLX_BLUE_SIZE, 1,
    None
  };

  extern "C"
  {
    draw_buffer_config *choose_best_draw_buffer_config()
    {
      Display *display = opengl_core::x11_display_thread_specific_acquire();
      int fbcount;
      GLXFBConfig *fbc = ::glXChooseFBConfig(display, DefaultScreen(display),
        visual_attribs, &fbcount);

      draw_buffer_config *ret = nullptr;
      if (fbc) {
        errno = 0;
        ret = (GLXFBConfig *)std::calloc(1, sizeof(GLXFBConfig));
        if (ret == nullptr || errno != 0) {
          std::cerr << "Failed to create internal resources for "
            << "draw_buffer_config" << std::endl << std::flush;
          opengl_core::x11_display_thread_specific_release();
          ::XFree(fbc);
          throw std::runtime_error("Internal Failure!!!");
        }

        ret = (GLXFBConfig *)memcpy(ret, &fbc[0], sizeof(GLXFBConfig));
        if (ret == nullptr) {
          std::cerr << "Failed to create internal resources for "
            << "draw_buffer_config" << std::endl << std::flush;
          opengl_core::x11_display_thread_specific_release();
          ::XFree(fbc);
          throw std::runtime_error("Internal Failure!!!");
        }
      }
      ::XFree(fbc);
      opengl_core::x11_display_thread_specific_release();

      return ret;
    }

    void draw_buffer_config_free(draw_buffer_config *&dbc)
    {
      if (dbc) {
        free(dbc);
        dbc = nullptr;
      }
    }
  }
}

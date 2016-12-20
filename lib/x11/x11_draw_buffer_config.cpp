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

#include <cassert>
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
    draw_buffer_config choose_best_draw_buffer_config()
    {
      Display *display = x11_display_thread_specific_acquire();
      int fbcount;
      GLXFBConfig *fbc = ::glXChooseFBConfig(display, DefaultScreen(display),
        visual_attribs, &fbcount);
      if (!fbc) {
        std::cerr << "Failed to create internal resources for "
          << "draw_buffer_config" << std::endl << std::flush;
        x11_display_thread_specific_release();
        ::XFree(fbc);
        throw std::runtime_error("Internal Failure!!!");
      }

      int best_fbc = -1;
      int worst_fbc = -1;
      int best_num_samp = -1;
      int worst_num_samp = 999;

      for (int i=0; i<fbcount; ++i) {
        XVisualInfo *vi = glXGetVisualFromFBConfig(display, fbc[i]);
        if (vi) {
          int samp_buf;
          int samples;
          glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLE_BUFFERS,
            &samp_buf);
          glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLES, &samples);

          if (best_fbc < 0 || (samp_buf && samples > best_num_samp)) {
            best_fbc = i;
            best_num_samp = samples;
          }
          if (worst_fbc < 0 || (!samp_buf || samples < worst_num_samp)) {
            worst_fbc = i, worst_num_samp = samples;
          }
        }
        XFree(vi);
      }

      assert(best_fbc != -1 && "Internal error failed to find valid draw "
        " buffer configuration.");
      GLXFBConfig ret = fbc[best_fbc];
      ::XFree(fbc);
      x11_display_thread_specific_release();
      return ret;
    }

    void draw_buffer_config_free(draw_buffer_config &)
    {
    }
  }
}

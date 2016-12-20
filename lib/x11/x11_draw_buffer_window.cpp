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
#include "opengl_core/core/draw_buffer_window.h"

#include "opengl_core/core/x11/x11_display.h"

#include <iostream>
#include <stdexcept>

namespace opengl_core
{
  extern "C"
  {
    draw_buffer_window draw_buffer_window_create(draw_buffer_config &dbc,
      int origin_x, int origin_y, int width, int height)
    {
      Display *display = x11_display_thread_specific_acquire();

      XVisualInfo *vi = glXGetVisualFromFBConfig(display, dbc);
      if (!vi) {
        std::cerr << "Failed to create internal resources for "
          << "draw_buffer_window" << std::endl << std::flush;
        XFree(vi);
        x11_display_thread_specific_release();
        throw std::runtime_error("Internal Failure!!!");
      }

      XSetWindowAttributes swa;
      swa.colormap = XCreateColormap(display,
        RootWindow(display, vi->screen), vi->visual, AllocNone);
      swa.border_pixel = 0;
      swa.event_mask = StructureNotifyMask;

      Window win = XCreateWindow(display, RootWindow(display, vi->screen),
        origin_x, origin_y, width, height, 0,
        vi->depth, InputOutput, vi->visual,
        CWBorderPixel | CWColormap | CWEventMask, &swa);
      if (!win) {
        std::cerr << "Failed to create internal resources for "
          << "draw_buffer_window" << std::endl << std::flush;
        XFree(vi);
        x11_display_thread_specific_release();
        throw std::runtime_error("Internal Failure!!!");
      }

      XFree(vi);
      x11_display_thread_specific_release();
      return win;
    }

    void draw_buffer_window_show(draw_buffer_window &win)
    {
      Display *display = x11_display_thread_specific_acquire();
      auto old_handler = XSetErrorHandler([](
        Display *display, XErrorEvent *error) -> int {
          if (error && error->error_code == BadWindow) {
            std::cerr << "Failed to create show draw_buffer_window"
              << "draw_buffer_window" << std::endl << std::flush;
            x11_display_thread_specific_release();
            throw std::runtime_error("Internal Failure!!!");
          }
          return -1;
      });
      XMapWindow(display, win);
      XSetErrorHandler(old_handler);
      x11_display_thread_specific_release();
    }

    void draw_buffer_window_free(draw_buffer_window &win)
    {
      Display *display = x11_display_thread_specific_acquire();
      XDestroyWindow(display, win);
      x11_display_thread_specific_release();
    }
  }
}

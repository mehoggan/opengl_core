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
#include "opengl_core/core/standard_renderer.h"

#include "opengl_core/core/x11/x11_display.h"
#include "opengl_core/core/draw_buffer_context.h"
#include "opengl_core/core/draw_buffer_window.h"

#include <iostream>
#include <stdexcept>

namespace opengl_core
{
  extern "C"
  {
    bool standard_event_loop_init()
    {
      bool ret = true;

      return ret;
    }

    void standard_event_loop_run(draw_buffer_window& win,
        draw_buffer_context& ctx)
    {
      Display *display = x11_display_thread_specific_acquire();

      bool terminate = false;
      bool exposed = false;
      XEvent x_event;
      Atom close_window;

      close_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
      if (!::XSetWMProtocols(display, win, &close_window, 1)) {
        std::cerr << "Unable to create 3.2 or higher OpenGL context."
          << std::endl << std::flush;
        x11_display_thread_specific_release();
        throw std::runtime_error("Internal Failure!!!");

      }

      while (!terminate) {
        int n = XEventsQueued(display, QueuedAfterReading);
        while (n--) {
          XNextEvent(display, &x_event);
          if (x_event.type == Expose) {
            exposed = true;
          } else if (x_event.type == ClientMessage) {
            if ((Atom)x_event.xclient.data.l[0] == close_window) {
              terminate = true;
            }
          }
        }

        if (terminate || !exposed) {
          continue;
        }

        opengl_core::draw_buffer_context_make_current(ctx, win);
        {
          glViewport(0, 0, 800, 600);
          glClearColor (0, 0.5, 1, 1);
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glBegin(GL_QUADS);
          {
            glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
            glColor3f(0., 1., 0.); glVertex3f(.75, -.75, 0.);
            glColor3f(0., 0., 1.); glVertex3f(.75,  .75, 0.);
            glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
          }
          glEnd();
          opengl_core::swap_buffers(win);
        }
        ctx = opengl_core::draw_buffer_context_get_current();
        opengl_core::draw_buffer_context_make_not_current(ctx);
      }

      x11_display_thread_specific_release();
    }
  }
}

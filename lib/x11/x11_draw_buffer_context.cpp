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
#include "opengl_core/core/draw_buffer_context.h"

#include "opengl_core/core/x11/x11_display.h"
#include "opengl_core/core/x11/x11_extension_checker.h"

#include <iostream>
#include <stdexcept>

#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092

namespace opengl_core
{
  extern "C"
  {
    OPENGL_CORE_API draw_buffer_context draw_buffer_context_create(
      draw_buffer_config &dbc, int major_version, int minor_version)
    {
      Display *display = x11_display_thread_specific_acquire();

      typedef GLXContext (*glXCreateContextAttribsARBProc)(
        Display*, GLXFBConfig, GLXContext, Bool, const int*);

      glXCreateContextAttribsARBProc glXCreateContextAttribsARB = NULL;
      XVisualInfo *vi = glXGetVisualFromFBConfig(display, dbc);
      GLXContext ctx_old = glXCreateContext(display, vi, 0, GL_TRUE);
      glXCreateContextAttribsARB =  (glXCreateContextAttribsARBProc)
        glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");

      const char *glx_exts = ::glXQueryExtensionsString(display,
        DefaultScreen(display));
      if (!is_extension_supported(glx_exts, "GLX_ARB_create_context") ||
        !glXCreateContextAttribsARB){
        std::cerr << "Unable to create 3.2 or higher OpenGL context."
          << std::endl << std::flush;
        x11_display_thread_specific_release();
        throw std::runtime_error("Internal Failure!!!");
      }

      glXMakeCurrent(display, 0, 0);
      glXDestroyContext(display, ctx_old);
      XFree(vi);

      if (!glXCreateContextAttribsARB) {
        x11_display_thread_specific_release();
      }

      static int context_attribs[] =
      {
        GLX_CONTEXT_MAJOR_VERSION_ARB, major_version,
        GLX_CONTEXT_MINOR_VERSION_ARB, minor_version,
        None
      };

      std::cout << "Creating context" << std::endl;
      GLXContext ctx = glXCreateContextAttribsARB(display, dbc, nullptr,
        true, context_attribs);
      if (!ctx) {
        x11_display_thread_specific_release();
      }

      x11_display_thread_specific_release();
      return ctx;
    }

    draw_buffer_context draw_buffer_context_get_current()
    {
      return glXGetCurrentContext();
    }

    void draw_buffer_context_make_current(draw_buffer_context &ctx,
      draw_buffer_window &win)
    {
      Display *display = x11_display_thread_specific_acquire();
      glXMakeCurrent(display, win, ctx);
      x11_display_thread_specific_release();
    }

    void draw_buffer_context_make_not_current(
      draw_buffer_context &)
    {
      Display *display = x11_display_thread_specific_acquire();
      glXMakeCurrent(display, 0, 0);
      x11_display_thread_specific_release();
    }

    draw_buffer_context draw_buffer_context_make_shared(
      draw_buffer_context &ctx)
    {
      return nullptr;
    }

    void draw_buffer_context_free(draw_buffer_context &ctx)
    {
      Display *display = x11_display_thread_specific_acquire();
      glXDestroyContext(display, ctx);
      x11_display_thread_specific_release();
    }

    void swap_buffers(draw_buffer_window &win)
    {
      Display *display = x11_display_thread_specific_acquire();
      glXSwapBuffers(display, win);
      x11_display_thread_specific_release();
    }
  }
}

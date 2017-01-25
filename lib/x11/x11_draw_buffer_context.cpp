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

#include "opengl_core/core/gl_utils.h"
#include "opengl_core/core/x11/x11_display.h"
#include "opengl_core/core/x11/x11_extension_checker.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <string.h>

#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092

namespace opengl_core
{
  extern "C"
  {
    OPENGL_CORE_API draw_buffer_context draw_buffer_context_create(
      draw_buffer_config &dbc, const gl_version &ctx_ver)
    {
      Display *display = x11_display_thread_specific_acquire();

      typedef GLXContext (*glXCreateContextAttribsARBProc)(
        Display*, GLXFBConfig, GLXContext, Bool, const int*);

      glXCreateContextAttribsARBProc glXCreateContextAttribsARB = NULL;
      XVisualInfo *vi = glXGetVisualFromFBConfig(display, dbc);
      GLXContext ctx_old = glXCreateContext(display, vi, 0, GL_TRUE);
      glXCreateContextAttribsARB =  (glXCreateContextAttribsARBProc)
        glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
        GL_CALL(glXGetProcAddress)

      const char *glx_exts = ::glXQueryExtensionsString(display,
        DefaultScreen(display));
      if (!is_extension_supported(glx_exts, "GLX_ARB_create_context") ||
        !glXCreateContextAttribsARB){
        std::cerr << "Unable to create 3.2 or higher OpenGL context."
          << std::endl << std::flush;
        x11_display_thread_specific_release();
        throw std::runtime_error("Internal Failure!!!");
      }

      glXMakeCurrent(display, 0, 0); GL_CALL(glXMakeCurrent)
      glXDestroyContext(display, ctx_old); GL_CALL(glXDestroyContext)
      XFree(vi);

      if (!glXCreateContextAttribsARB) {
        x11_display_thread_specific_release();
      }

      static int context_attribs[] =
      {
        GLX_CONTEXT_MAJOR_VERSION_ARB, ctx_ver.major,
        GLX_CONTEXT_MINOR_VERSION_ARB, ctx_ver.minor,
        None
      };

      std::cout << "Creating context" << std::endl;
      GLXContext ctx = glXCreateContextAttribsARB(display, dbc, nullptr,
        true, context_attribs); GL_CALL(glXCreateContextAttribsARB)
      if (!ctx) {
        x11_display_thread_specific_release();
      }

      x11_display_thread_specific_release();
      return ctx;
    }

    draw_buffer_context draw_buffer_context_get_current()
    {
      return glXGetCurrentContext(); GL_CALL(glXGetCurrentContext)
    }

    void draw_buffer_context_make_current(draw_buffer_context &ctx,
      draw_buffer_window &win)
    {
      Display *display = x11_display_thread_specific_acquire();
      glXMakeCurrent(display, win, ctx); GL_CALL(glXMakeCurrent)
      x11_display_thread_specific_release();
    }

    void draw_buffer_context_make_not_current(
      draw_buffer_context &)
    {
      Display *display = x11_display_thread_specific_acquire();
      glXMakeCurrent(display, 0, 0); GL_CALL(glXMakeCurrent)
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
      glXDestroyContext(display, ctx); GL_CALL(glXDestroyContext)
      x11_display_thread_specific_release();
    }

    void swap_buffers(draw_buffer_window &win)
    {
      Display *display = x11_display_thread_specific_acquire();
      glXSwapBuffers(display, win); GL_CALL(glXSwapBuffers)
      x11_display_thread_specific_release();
    }

    gl_version draw_buffer_context_version(
      draw_buffer_context &ctx, draw_buffer_window &win)
    {
      gl_version ret{0, 0};

      glGetIntegerv(GL_MAJOR_VERSION, (GLint *)(&ret.major));
      GL_CALL(glGetIntegerv(GL_MAJOR_VERSION));
      glGetIntegerv(GL_MINOR_VERSION, (GLint *)(&ret.minor));
      GL_CALL(glGetIntegerv(GL_MINOR_VERSION));

      return ret;
    }
  }
}

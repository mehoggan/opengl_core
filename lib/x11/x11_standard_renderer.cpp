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

#include "opengl_core/core/draw_buffer_context.h"
#include "opengl_core/core/draw_buffer_window.h"
#include "opengl_core/core/gl_utils.h"
#include "opengl_core/core/x11/x11_display.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

namespace opengl_core
{
  static pthread_key_t pthread_init_callback_key;
  static pthread_key_t pthread_pre_render_callback_key;
  static pthread_key_t pthread_render_callback_key;
  static pthread_key_t pthread_post_render_callback_key;
  static pthread_key_t pthread_close_callback_key;

  extern "C"
  {
    static void init_cb_dtor(void *init_cb)
    {
      if (init_cb) {
        delete (init_callback *)init_cb;
      }
    }

    static void pre_render_cb_dtor(void *pre_render_cb)
    {
      if (pre_render_cb) {
        delete (pre_render_callback *)pre_render_cb;
      }
    }

    static void render_cb_dtor(void *render_cb)
    {
      if (render_cb) {
        delete (pre_render_callback *)render_cb;
      }
    }

    static void post_render_cb_dtor(void *post_render_cb)
    {
      if (post_render_cb) {
        delete (pre_render_callback *)post_render_cb;
      }
    }

    static void close_cb_dtor(void *close_cb)
    {
      if (close_cb) {
        delete (close_callback *)close_cb;
      }
    }

    bool standard_event_loop_init()
    {
      std::cout << "Standard event loop initialized." << std::endl;
      int status;
      bool ret = true;

      if (ret) {
        errno = 0;
        status = pthread_key_create(&pthread_init_callback_key,
          init_cb_dtor);
        if (status || errno != 0) {
          std::cerr << std::strerror(errno) << std::endl << std::flush;
          ret = false;
        }
      }

      if (ret) {
        errno = 0;
        status = pthread_key_create(&pthread_pre_render_callback_key,
          pre_render_cb_dtor);
        if (status || errno != 0) {
          std::cerr << std::strerror(errno) << std::endl << std::flush;
          ret = false;
        }
      }

      if (ret) {
        errno = 0;
        status = pthread_key_create(&pthread_render_callback_key,
          render_cb_dtor);
        if (status || errno != 0) {
          std::cerr << std::strerror(errno) << std::endl << std::flush;
          ret = false;
        }
      }

      if (ret) {
        errno = 0;
        status = pthread_key_create(&pthread_post_render_callback_key,
          post_render_cb_dtor);
        if (status || errno != 0) {
          std::cerr << std::strerror(errno) << std::endl << std::flush;
          ret = false;
        }
      }

      if (ret) {
        errno = 0;
        status = pthread_key_create(&pthread_close_callback_key,
          close_cb_dtor);
        if (status || errno != 0) {
          std::cerr << std::strerror(errno) << std::endl << std::flush;
          ret = false;
        }
      }

      return ret;
    }

    void set_thread_local_init_callback(const init_callback &cb)
    {
      int status;
      auto *init = (init_callback *)pthread_getspecific(
        pthread_init_callback_key);
      if (!init) {
        init = new init_callback(cb);
        status = pthread_setspecific(pthread_init_callback_key, init);
        if (status) {
          std::cerr << "Unable to set thread local init callback."
            << std::endl << std::flush;
          throw std::runtime_error("Internal Failure!!!");
        }
      } else {
        (*init) = cb;
      }
    }

    void set_thread_local_pre_render_callback(const pre_render_callback &cb)
    {
      int status;
      auto *pre_render = (pre_render_callback *)pthread_getspecific(
        pthread_pre_render_callback_key);
      if (!pre_render) {
        pre_render = new pre_render_callback(cb);
        status = pthread_setspecific(pthread_pre_render_callback_key,
          pre_render);
        if (status) {
          std::cerr << "Unable to set thread local pre_render callback."
            << std::endl << std::flush;
          throw std::runtime_error("Internal Failure!!!");
        }
      } else {
        (*pre_render) = cb;
      }
    }

    void set_thread_local_render_callback(const render_callback &cb)
    {
      int status;
      auto *render = (render_callback *)pthread_getspecific(
        pthread_render_callback_key);
      if (!render) {
        render = new render_callback(cb);
        status = pthread_setspecific(pthread_render_callback_key,
          render);
        if (status) {
          std::cerr << "Unable to set thread local render callback."
            << std::endl << std::flush;
          throw std::runtime_error("Internal Failure!!!");
        }
      } else {
        (*render) = cb;
      }
    }

    void set_thread_local_post_render_callback(
      const post_render_callback &cb)
    {
      int status;
      auto *post_render = (post_render_callback *)pthread_getspecific(
        pthread_post_render_callback_key);
      if (!post_render) {
        post_render = new post_render_callback(cb);
        status = pthread_setspecific(pthread_post_render_callback_key,
          post_render);
        if (status) {
          std::cerr << "Unable to set thread local post_render callback."
            << std::endl << std::flush;
          throw std::runtime_error("Internal Failure!!!");
        }
      } else {
        (*post_render) = cb;
      }
    }

    void set_thread_local_close_callback(const close_callback &cb)
    {
      int status;
      auto *close = (close_callback *)pthread_getspecific(
        pthread_close_callback_key);
      if (!close) {
        close = new close_callback(cb);
        status = pthread_setspecific(pthread_close_callback_key,
          close);
        if (status) {
          std::cerr << "Unable to set thread local close callback."
            << std::endl << std::flush;
          throw std::runtime_error("Internal Failure!!!");
        }
      } else {
        (*close) = cb;
      }
    }

    void standard_event_loop_run(draw_buffer_window& win,
        draw_buffer_context &ctx)
    {
      Display *display = x11_display_thread_specific_acquire();

      bool terminate = false;
      bool exposed = false;
      XEvent x_event;
      Atom close_window;

      close_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
      if (!::XSetWMProtocols(display, win, &close_window, 1)) {
        std::cerr << "Unable to set atom on window." << std::endl
          << std::flush;
        x11_display_thread_specific_release();
        throw std::runtime_error("Internal Failure!!!");
      }

      {
        auto *init = (init_callback *)pthread_getspecific(
          pthread_init_callback_key);
        if (init) {
          opengl_core::draw_buffer_context_make_current(ctx, win);
          (*init)(win, ctx);
          opengl_core::draw_buffer_context_make_not_current(ctx);
        }
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
          auto *pre_render = (pre_render_callback *)pthread_getspecific(
            pthread_pre_render_callback_key);
          if (pre_render) {
            (*pre_render)(win, ctx);
          }
        }
        {
          {
            auto *render = (render_callback *)pthread_getspecific(
              pthread_render_callback_key);
            if (render) {
              GL_CALL(null)
              (*render)(win, ctx);
            }
          }
          opengl_core::swap_buffers(win);
          {
            auto *post_render = (post_render_callback *)pthread_getspecific(
              pthread_post_render_callback_key);
            if (post_render) {
              (*post_render)(win, ctx);
            }
          }
        }
        ctx = opengl_core::draw_buffer_context_get_current();
        opengl_core::draw_buffer_context_make_not_current(ctx);
      }
      {
        auto *close = (close_callback *)pthread_getspecific(
          pthread_close_callback_key);
        if (close) {
          (*close)(win, ctx);
        }
      }
      x11_display_thread_specific_release();
    }
  }
}

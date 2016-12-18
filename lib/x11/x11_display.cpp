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
#include "opengl_core/core/x11/x11_display.h"

#include <cassert>
#include <cerrno>
#include <cstring>
#include <functional>
#include <iostream>

namespace opengl_core
{
  static pthread_key_t pthread_display_key;
  static pthread_key_t pthread_use_key;

  extern "C"
  {
    static void use_key_dtor(void *use_key)
    {
      if (use_key) {
        auto use = *((std::uint32_t *)use_key);
        assert(use == 0 && "User did not release all displays before "
          "thread exited.");
        delete (std::uint32_t *)use_key;
      }
    }

    bool x11_display_init()
    {
      int status;
      bool ret = true;

      if (ret) {
        errno = 0;
        status = pthread_key_create(&pthread_display_key, NULL);
        if (status || errno != 0) {
          std::cerr << std::strerror(errno) << std::endl << std::flush;
          ret = false;
        }
      }

      if (ret) {
        errno = 0;
        status = pthread_key_create(&pthread_use_key, use_key_dtor);
        if (status || errno != 0) {
          std::cerr << std::strerror(errno) << std::endl << std::flush;
          ret = false;
        }
      }

      return ret;
    }

    Display *x11_display_thread_specific_acquire()
    {
      auto *display = (Display *)pthread_getspecific(pthread_display_key);
      if (!display) {
        display = ::XOpenDisplay(NULL);
        pthread_setspecific(pthread_display_key, display);

        auto *d = (std::uint32_t *)pthread_getspecific(pthread_use_key);
        if (!d) {
          pthread_setspecific(pthread_use_key, new std::uint32_t(0));
        }
      }

      auto &use = *((std::uint32_t *)pthread_getspecific(pthread_use_key));
      ++(use);

      return display;
    }

    void x11_display_thread_specific_release()
    {
      auto &use = *((std::uint32_t *)pthread_getspecific(pthread_use_key));
      --(use);
      if (use == 0) {
        auto *display = (Display *)pthread_getspecific(pthread_display_key);
        ::XCloseDisplay(display);
        display = nullptr;
        pthread_setspecific(pthread_display_key, display);
      }
    }

    std::uint32_t x11_display_thread_specifc_use_count()
    {
      auto usep = (std::uint32_t *)pthread_getspecific(pthread_use_key);
      if (usep) {
        return *usep;
      } else {
        return 0;
      }
    }
  }
}

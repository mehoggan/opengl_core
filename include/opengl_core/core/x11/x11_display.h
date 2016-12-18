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
 *
 */
#ifndef OPENGL_CORE_X11_DISPLAY_H_INCLUDED
#define OPENGL_CORE_X11_DISPLAY_H_INCLUDED

#include "declspec.h"
#include <cstdint>
#include <X11/Xlib.h>

namespace opengl_core
{
  extern "C"
  {
    bool x11_display_init();
    Display *x11_display_thread_specific_acquire();
    void x11_display_thread_specific_release();

    std::uint32_t x11_display_thread_specifc_use_count();
  }
}
#endif

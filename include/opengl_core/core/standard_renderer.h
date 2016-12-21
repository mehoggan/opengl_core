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
#ifndef OPENGL_CORE_STANDARD_RENDERER_H_INCLUDED
#define OPENGL_CORE_STANDARD_RENDERER_H_INCLUDED

#include "declspec.h"

#include "opengl_core/core/platform.h"

namespace opengl_core
{
  extern "C"
  {
    OPENGL_CORE_API bool standard_event_loop_init();

    OPENGL_CORE_API void standard_event_loop_run(draw_buffer_window& win,
      draw_buffer_context& ctx);
  }
}

#endif

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
#ifndef OPENGL_CORE_DRAW_BUFFER_CONTEXT_H_INCLUDED
#define OPENGL_CORE_DRAW_BUFFER_CONTEXT_H_INCLUDED

#include "declspec.h"

#include "opengl_core/core/platform.h"
#include "opengl_core/core/draw_buffer_config.h"
#include "opengl_core/core/draw_buffer_window.h"

namespace opengl_core
{
  extern "C"
  {
    OPENGL_CORE_API draw_buffer_context draw_buffer_context_create(
      draw_buffer_config &dbc, int major_version, int minor_version);

    OPENGL_CORE_API draw_buffer_context draw_buffer_context_get_current();

    OPENGL_CORE_API void draw_buffer_context_make_current(
      draw_buffer_context &ctx, draw_buffer_window &win);

    OPENGL_CORE_API void draw_buffer_context_make_not_current(
      draw_buffer_context &ctx);

    OPENGL_CORE_API draw_buffer_context draw_buffer_context_make_shared(
      draw_buffer_context &ctx);

    OPENGL_CORE_API void draw_buffer_context_free(draw_buffer_context ctx);

    OPENGL_CORE_API void swap_buffers(draw_buffer_window win);
  }
}

#endif


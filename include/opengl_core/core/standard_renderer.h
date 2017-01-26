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

#include "opengl_core/core/draw_buffer_context.h"
#include "opengl_core/core/draw_buffer_window_config.h"
#include "opengl_core/core/platform.h"

#include <functional>

namespace opengl_core
{
  extern "C"
  {
    OPENGL_CORE_API bool standard_event_loop_init();

    typedef std::function<void (draw_buffer_window &,
      draw_buffer_context &)> init_callback;
    OPENGL_CORE_API void set_thread_local_init_callback(
      const init_callback &cb);

    typedef std::function<void (draw_buffer_window &,
      draw_buffer_context &)> pre_render_callback;
    OPENGL_CORE_API void set_thread_local_pre_render_callback(
      const pre_render_callback &cb);

    typedef std::function<void (draw_buffer_window &,
      draw_buffer_context &)> render_callback;
    OPENGL_CORE_API void set_thread_local_render_callback(
      const render_callback &cb);

    typedef std::function<void (draw_buffer_window &,
      draw_buffer_context &)> post_render_callback;
    OPENGL_CORE_API void set_thread_local_post_render_callback(
      const post_render_callback &cb);

    typedef std::function<void (draw_buffer_window &,
      draw_buffer_context &)> close_callback;
    OPENGL_CORE_API void set_thread_local_close_callback(
      const close_callback &cb);

    OPENGL_CORE_API void standard_event_loop_run(
      const gl_version &ctx_ver,
      const draw_buffer_window_config &win_conf);
  }
}

#endif

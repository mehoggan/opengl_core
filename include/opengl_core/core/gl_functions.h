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
#ifndef GL_FUNCTIONS_HPP_INCLUDED
#define GL_FUNCTIONS_HPP_INCLUDED

#include "declspec.h"

#include "opengl_core/core/draw_buffer_context.h"
#include "opengl_core/core/gl_utils.h"

#include <cstdint>

namespace opengl_core
{
  /**
   * This struct's function should only be called while a context has been
   * made current. The loading of extensions differs from platform to
   * platform. It should also be noted that this struct's public static
   * function should be called by the thread who owns the context.
   */
  struct gl_functions
  {
  private:
    OPENGL_CORE_API static void load_1_2();
    OPENGL_CORE_API static void load_1_3();
    OPENGL_CORE_API static void load_1_4();
    OPENGL_CORE_API static void load_1_5();
    OPENGL_CORE_API static void load_2_0();
    OPENGL_CORE_API static void load_2_1();
    OPENGL_CORE_API static void load_3_0();
    OPENGL_CORE_API static void load_3_1();
    OPENGL_CORE_API static void load_3_2();
    OPENGL_CORE_API static void load_3_3();
    OPENGL_CORE_API static void load_4_0();
    OPENGL_CORE_API static void load_4_1();
    OPENGL_CORE_API static void load_4_2();
    OPENGL_CORE_API static void load_4_3();
    OPENGL_CORE_API static void load_4_4();
    OPENGL_CORE_API static void load_4_5();

  public:
    static void configure(const gl_version &ctx_ver);
  };
}
#endif

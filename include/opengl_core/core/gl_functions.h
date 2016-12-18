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

#include "opengl_core/core/symbol_loader.h"

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
    OPENGL_CORE_API static void load_1_2(symbol_loader *sym_loader);
    OPENGL_CORE_API static void load_1_3(symbol_loader *sym_loader);
    OPENGL_CORE_API static void load_1_4(symbol_loader *sym_loader);
    OPENGL_CORE_API static void load_1_5(symbol_loader *sym_loader);
    OPENGL_CORE_API static void load_2_0(symbol_loader *sym_loader);
    OPENGL_CORE_API static void load_2_1(symbol_loader *sym_loader);
    OPENGL_CORE_API static void load_3_0(symbol_loader *sym_loader);

  public:
    static void configure(const std::uint8_t major,
      const std::uint8_t minor);
  };
}
#endif

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
#ifndef RENDER_SYSTEM_H_INCLUDED
#define RENDER_SYSTEM_H_INCLUDED

#include "declspec.h"

#include "opengl_core/core/non_copyable.h"

namespace opengl_core
{
  class OPENGL_CORE_API render_system : public non_copyable
  {
  private:
    struct render_system_impl;
    render_system_impl *m_impl;

  private:
    void render_loop();

  public:
    render_system();
    ~render_system();

    bool init_system();
    void terminate();
    void destroy();
  };
}

#endif

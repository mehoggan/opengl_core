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

#include <cstdint>
#include <functional>

namespace opengl_core
{
  class OPENGL_CORE_API render_system : public non_copyable
  {
  public:
    struct render_system_impl;

  private:
    render_system_impl *m_impl;

  public:
    typedef std::function<void (render_system &system)>
      init_function;
    typedef std::function<void (render_system &system)>
      pre_render_function;
    typedef std::function<void (render_system &system, std::size_t millis)>
      render_function;
    typedef std::function<void (render_system &system)>
      post_render_function;
    typedef std::function<void (render_system &system)>
      shutdown_function;

  public:
    render_system(init_function &init, pre_render_function &pre_render,
      render_function &render, post_render_function &post_render,
      shutdown_function &shutdown, bool threaded = false);
    ~render_system();

    bool init_system();
    void terminate_system();
    void destroy();
    void *impl();
  };
}

#endif

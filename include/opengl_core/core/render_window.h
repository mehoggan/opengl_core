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
#ifndef RENDER_WINDOW_H_INCLUDED
#define RENDER_WINDOW_H_INCLUDED

#include "opengl_core/core/non_copyable.h"

#include "opengl_core/core/fb_config.h"

#include <memory>

namespace opengl_core
{
  class render_system;

  class render_window : public non_copyable
  {
  private:
    struct window_impl;
    window_impl *m_impl;

  public:
    render_window();
    ~render_window();

    void init(render_system &system, fb_config &fbc);
    void map();
    void destroy();

    void *impl();
  };
}

#endif

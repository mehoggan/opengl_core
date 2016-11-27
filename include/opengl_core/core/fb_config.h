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
#ifndef FB_CONFIG_H_INCLUDED
#define FB_CONFIG_H_INCLUDED

#include "opengl_core/core/non_copyable.h"

#include <memory>

namespace opengl_core
{
  class render_system;
  class render_window;

  class fb_config : public non_copyable
  {
  private:
    struct fb_config_impl;
    fb_config_impl *m_impl;

  public:
    fb_config();
    ~fb_config();

    void choose_best(render_system &system, render_window *detail = nullptr);
    void destroy();

    void *impl();
  };
}

#endif

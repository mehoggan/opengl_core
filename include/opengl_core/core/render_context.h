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
#ifndef RENDER_CONTEXT_H_INCLUDED
#define RENDER_CONTEXT_H_INCLUDED

#include "opengl_core/core/non_copyable.h"

#include "opengl_core/core/fb_config.h"
#include "opengl_core/core/render_window.h"

#include <memory>

namespace opengl_core
{
  class render_context : public non_copyable
  {
  private:
    struct context_impl;
    context_impl *m_impl;

  public:
    render_context();
    ~render_context();

    void init(render_system &system, render_window &window, fb_config &fbc);
    void make_current(render_window &window);
    void make_not_current();
    void destroy();

    void *impl();

    int query_major_version() const;
    int query_minor_version() const;
  };
}


#endif

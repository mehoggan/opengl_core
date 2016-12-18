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
#ifndef SYMBOL_LOADER_H_INCLUDED
#define SYMBOL_LOADER_H_INCLUDED

#include "opengl_core/core/non_copyable.h"

#include <iostream>

namespace opengl_core
{
  class OPENGL_CORE_API symbol_loader : public non_copyable
  {
  private:
    void *m_handle;
    const char *m_lib_name;
    bool m_good;

  public:
    explicit symbol_loader(const char *lib_name);
    ~symbol_loader();

    bool get_good() const { return m_good; }

    void *load(const char *symb_name);

  private:
    void print_error();
  };
}

#endif

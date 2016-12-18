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
#include "opengl_core/core/symbol_loader.h"

#include <dlfcn.h>

namespace opengl_core
{
  symbol_loader::symbol_loader(const char *lib_name) :
    m_lib_name(lib_name),
    m_good(false)
  {
    m_handle = dlopen(lib_name, RTLD_GLOBAL | RTLD_LAZY);

    if (!m_handle) {
      print_error();
    } else {
      m_good = true;
    }
  }

  symbol_loader::~symbol_loader()
  {
    int status = dlclose(m_handle);
    if (status) {
      print_error();
    }
  }

  void *symbol_loader::load(const char *symb_name)
  {
    void *func = nullptr;
    if (m_good) {
      func = dlsym(m_handle, symb_name);
      if (func == nullptr) {
        std::cerr << "Failed to load " << symb_name << " from "
          << m_lib_name << std::endl;
        print_error();
      }
    }

    return func;
  }

  void symbol_loader::print_error()
  {
    const char *errstr = dlerror();
    std::cerr << errstr << std::endl;
  }
}

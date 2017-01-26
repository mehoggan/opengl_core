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
#ifndef OPENGL_CORE_SPIN_LOCK_H_INCLUDED
#define OPENGL_CORE_SPIN_LOCK_H_INCLUDED

#include "declspec.h"

#include <cstdint>

namespace opengl_core
{
  class OPENGL_CORE_API draw_buffer_window_config
  {
  private:
    std::size_t m_ul_x;
    std::size_t m_ul_y;
    std::size_t m_width;
    std::size_t m_height;

  public:
    draw_buffer_window_config(std::size_t ul_x, std::size_t ul_y,
      std::size_t width, std::size_t height);

    std::size_t upper_left_x() const;
    std::size_t upper_left_y() const;
    std::size_t width() const;
    std::size_t height() const;
  };
}

#endif

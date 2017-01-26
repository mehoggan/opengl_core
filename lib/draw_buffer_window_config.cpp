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
#include "opengl_core/core/draw_buffer_window_config.h"

namespace opengl_core
{

  draw_buffer_window_config::draw_buffer_window_config(std::size_t ul_x,
    std::size_t ul_y, std::size_t width, std::size_t height) :
    m_ul_x(ul_x),
    m_ul_y(ul_y),
    m_width(width),
    m_height(height)
  {}

  std::size_t draw_buffer_window_config::upper_left_x() const
  {
    return m_ul_x;
  }

  std::size_t draw_buffer_window_config::upper_left_y() const
  {
    return m_ul_y;
  }

  std::size_t draw_buffer_window_config::width() const
  {
    return m_width;
  }

  std::size_t draw_buffer_window_config::height() const
  {
    return m_height;
  }
}


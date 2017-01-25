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

#include <cassert>
#include <iostream>

#define DEBUG_GL 1

#if DEBUG_GL
#define GL_OUTPUT(func) \
  std::cout << "file = " << __FILE__ \
    << " line = " << __LINE__ \
    << " error = " << error \
    << " opengl function = " << #func \
    << std::endl << std::flush;
#else
#define GL_OUTPUT {int x = 0; x = x;}
#endif

#define GL_CALL(func) do { \
    GLint error; \
    while ((error = glGetError()) != 0) { \
      GL_OUTPUT(func) \
    } \
  } while(false);

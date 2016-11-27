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
#ifndef OPENGL_CORE_PLATFORM_H_INCLUDED
#define OPENGL_CORE_PLATFORM_H_INCLUDED

#if defined(__ANDROID__)
  #define __OPENGL_CORE_ANDROID__ 1
  #define msvc_typename
#elif defined(__CYGWIN__)
  #define __OPENGL_CORE_CYGWIN__ 1
  #define msvc_typename
#elif defined(__gnu_linux__) || defined(__linux__)
  #define __OPENGL_CORE_GNULINUX__ 1
  #define msvc_typename
#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__)
  #define __OPENGL_CORE_MACOSX__ 1
  #define msvc_typename
#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
  #define __OPENGL_CORE_WINDOWS__ 1
  #define msvc_typename typename
  #if defined(_WIN16)
    #define __OPENGL_CORE_16_BIT__ 1
  #elif defined(_WIN32)
    #define __OPENGL_CORE_32_BIT__ 1
  #elif defined(_M_IA64) || defined(_M_AMD64) || defined(__x86_64__) || \
    defined(__x86_64)
    #define __OPENGL_CORE_64_BIT__ 1
  #else
    #define __OPENGL_CORE_32_BIT__ 1
  #endif
#endif

#endif

#ifndef OPENGL_CORE_WIN32_HINSTANCE_H_INCLUDED
#define OPENGL_CORE_WIN32_HINSTANCE_H_INCLUDED

#include <Windows.h>

#include <cstdint>
#include <atomic>

namespace opengl_core
{
  class win32_hinstance
  {
  public:
    typedef HINSTANCE Win32_HInstance;

  private:
    static Win32_HInstance s_hinstance;

  public:
    static Win32_HInstance &acquire();
  };
}

#endif
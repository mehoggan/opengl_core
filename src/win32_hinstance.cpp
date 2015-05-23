#include <core/win32_hinstance.h>

#include <cassert>
#include <iostream>

namespace opengl_core
{
  win32_hinstance::Win32_HInstance win32_hinstance::s_hinstance = 0;

  win32_hinstance::Win32_HInstance &win32_hinstance::acquire()
  {
    if (s_hinstance == 0) {
      s_hinstance = ::GetModuleHandle(0);
      assert(s_hinstance && "Failed to acquire HINSTANCE");
    }

    return s_hinstance;
  }
}
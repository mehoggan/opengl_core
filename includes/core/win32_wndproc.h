#ifndef WIN32_WNDPROC_H_INCLUDED
#define WIN32_WNDPROC_H_INCLUDED

#include <Windows.h>

namespace opengl_core
{
  extern "C" LRESULT CALLBACK wnd_proc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam);
}

#endif
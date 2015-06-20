#include <core/win32_wndproc.h>

#include <core/fb_config.h>
#include <core/render_system.h>
#include <core/render_window.h>

#define nop {int x = 0; x = x;}
namespace opengl_core
{
  LRESULT CALLBACK wnd_proc(HWND h_wnd, UINT message, WPARAM w_param,
    LPARAM l_param)
  {
    if (message == WM_NCCREATE) {
      render_window *wdgt = (render_window*)(((CREATESTRUCT*)l_param)->
        lpCreateParams);
      if (wdgt) {
        ::SetWindowLongPtr(h_wnd, GWLP_USERDATA, (LONG_PTR)wdgt);
      }
      return ::DefWindowProc(h_wnd, message, w_param, l_param);
    }

    switch (message) {
    case WM_CREATE: {
      int x = 0; x = x;
    }
      break;
    case WM_DESTROY: {
      ::PostQuitMessage(0);
    }
      break;
    case WM_QUIT: {
      nop
    }
      break;
    default: {
      return ::DefWindowProc(h_wnd, message, w_param, l_param);
    }
    }

    return 0;
  }
}
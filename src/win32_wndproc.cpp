#include "core/win32_wndproc.h"

#include "core/fb_config.h"
#include "core/render_system.h"

#include <unordered_map>

namespace opengl_core
{
  std::unordered_map<HWND, render_system*> g_systems;

  LRESULT CALLBACK wnd_proc(HWND h_wnd, UINT message, WPARAM w_param,
    LPARAM l_param)
  {
    if (message == WM_NCCREATE) {
      render_system *system = (render_system*)(((CREATESTRUCT*)l_param)->
        lpCreateParams);
      if (system) {
        g_systems[h_wnd] = system;
      }
      return ::DefWindowProc(h_wnd, message, w_param, l_param);
    }

    switch (message) {
    case WM_CREATE: {
    }
      break;
    case WM_DESTROY: {
      ::PostQuitMessage(0);
      auto it = g_systems.find(h_wnd);
      if (it != g_systems.end()) {
        it->second->terminate();
      }
    }
      break;
    case WM_QUIT: {
      g_systems.erase(g_systems.find(h_wnd));
    }
      break;
    default: {
      return ::DefWindowProc(h_wnd, message, w_param, l_param);
    }
    }

    return 0;
  }
}

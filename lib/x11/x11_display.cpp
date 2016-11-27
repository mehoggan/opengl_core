#include "opengl_core/core/x11_display.h"

#include <cassert>
#include <iostream>

namespace opengl_core
{
  thread_local x11_display::X11_Display *x11_display::s_display = NULL;
  thread_local uint32_t x11_display::s_use_count = 0u;

  x11_display::X11_Display *&x11_display::acquire()
  {
    if (s_use_count == 0) {
      s_display = ::XOpenDisplay(NULL); // Open local display only
      assert(s_display && "Failed to open XDisplay");
    }
    ++s_use_count;

    return s_display;
  }

  void x11_display::sync(bool flush_events)
  {
    ::XSync(s_display, flush_events ? True : False);
  }

  void x11_display::release()
  {
    if (s_use_count == 1u) {
      ::XCloseDisplay(s_display);
      s_display = 0;
    }
    --s_use_count;
  }
}

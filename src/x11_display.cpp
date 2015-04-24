#include <core/x11_display.h>

#include <iostream>

namespace opengl_core
{
  thread_local x11_display::X11_Display *x11_display::s_display = NULL;
  thread_local std::atomic<uint32_t> x11_display::s_use_count =
    ATOMIC_VAR_INIT(0u);

  x11_display::X11_Display *&x11_display::acquire()
  {
    uint32_t tmp = 0u;
    if (std::atomic_compare_exchange_strong(&s_use_count, &tmp, 1u)) {
      s_display = ::XOpenDisplay(NULL); // Open local display only
      assert(s_display && "Failed to open XDisplay");
    } else {
      ::XLockDisplay(s_display);
      std::atomic_fetch_add(&s_use_count, 1u);
      ::XUnlockDisplay(s_display);
    }

    return s_display;
  }

  void x11_display::lock()
  {
    ::XLockDisplay(s_display);
  }

  void x11_display::unlock()
  {
    ::XUnlockDisplay(s_display);
  }

  void x11_display::sync(bool flush_events)
  {
    ::XSync(s_display, flush_events ? True : False);
  }

  void x11_display::release()
  {
    uint32_t tmp = 1u;
    if (std::atomic_compare_exchange_strong(&s_use_count, &tmp, 0u)) {
      ::XCloseDisplay(s_display);
      s_display = 0;
    } else {
      ::XLockDisplay(s_display);
      std::atomic_fetch_sub(&s_use_count, 1u);
      ::XUnlockDisplay(s_display);
    }
  }
}

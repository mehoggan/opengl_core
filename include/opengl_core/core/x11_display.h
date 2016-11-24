#ifndef OPENGL_CORE_X11_DISPLAY_H_INCLUDED
#define OPENGL_CORE_X11_DISPLAY_H_INCLUDED

#include "declspec.h"

#include <X11/Xlib.h>

#include <cstdint>

namespace opengl_core
{
  class OPENGL_CORE_API x11_display
  {
  private:
    typedef Display X11_Display;
    static thread_local X11_Display *s_display;
    static thread_local uint32_t s_use_count;

  public:
    static thread_local X11_Display *&acquire();
    static thread_local void lock();
    static thread_local void unlock();
    static thread_local void sync(bool flush_events = true);
    static thread_local void release();

    static thread_local uint32_t &use_count() {return s_use_count;}
  };
}

#endif

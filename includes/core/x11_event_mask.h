#ifndef OPENGL_CORE_X11_EVENT_MASK_H_INCLUDED
#define OPENGL_CORE_X11_EVENT_MASK_H_INCLUDED

#include <declspec.h>

#include <X11/Xlib.h>

namespace opengl_core
{
  struct events
  {
    static const long mask = (FocusChangeMask | EnterWindowMask | LeaveWindowMask |
      ExposureMask | ButtonPressMask | ButtonReleaseMask |  PointerMotionMask |
      KeyPressMask | KeyReleaseMask | PropertyChangeMask | StructureNotifyMask |
      KeymapStateMask);
  };
}

#endif

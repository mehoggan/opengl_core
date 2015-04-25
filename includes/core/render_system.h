#ifndef RENDER_SYSTEM_H_INCLUDED
#define RENDER_SYSTEM_H_INCLUDED

#include <declspec.h>

namespace opengl_core
{
  class render_system
  {
  private:
    static thread_local int m_major_version;
    static thread_local int m_minor_version;

  public:
    static thread_local bool init(const int major, const int minor);
    static thread_local void destroy();
  };
}

#endif

#ifndef NON_COPYABLE_HPP_INCLUDED
#define NON_COPYABLE_HPP_INCLUDED

#include <declspec.h>

namespace opengl_core
{
  class OPENGL_CORE_API non_copyable
  {
  protected:
    non_copyable() {}
    ~non_copyable() {}

  private:
    non_copyable(const non_copyable &) = delete;
    non_copyable &operator=(const non_copyable &) = delete;
    non_copyable(non_copyable &&) = delete;
  };
}
#endif

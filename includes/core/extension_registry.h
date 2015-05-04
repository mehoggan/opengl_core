#ifndef EXTENSION_REGISTRY_H_INCLUDED
#define EXTENSION_REGISTRY_H_INCLUDED

#include <core/non_copyable.h>

#include <functional>
#include <unordered_set>
#include <utility>
#include <vector>

#include <GL/gl.h>

namespace opengl_core
{
  struct registry_item
  {
  public:
    std::pair<GLshort, GLshort> m_major_minor;
    std::vector<std::string> m_extensions;

  public:
    registry_item(GLshort major, GLshort minor);

    friend bool operator==(const registry_item &lhs, const registry_item &rhs)
    {
      return lhs.m_major_minor == rhs.m_major_minor;
    }
  };
}

namespace std
{
  template<>
  struct hash<opengl_core::registry_item>
  {
    size_t operator()(const opengl_core::registry_item &i) const
    {
      GLint x = i.m_major_minor.first;
      x &= 0x0000ffff;
      x = (x | (x << 8)) & 0x00ff00ff;
      x = (x | (x << 4)) & 0x0f0f0f0f;
      x = (x | (x << 2)) & 0x33333333;
      x = (x | (x << 1)) & 0x55555555;

      GLint y = i.m_major_minor.second;
      y &= 0x0000ffff;
      y = (y | (y << 8)) & 0x00ff00ff;
      y = (y | (y << 4)) & 0x0f0f0f0f;
      y = (y | (y << 2)) & 0x33333333;
      y = (y | (y << 1)) & 0x55555555;

      return (x | (y << 1));
    }
  };
}

namespace opengl_core
{
  class extension_registry : public non_copyable
  {
  private:
    std::unordered_set<registry_item> m_table;

  public:
    void init();
  };
}

#endif

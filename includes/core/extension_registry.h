#ifndef EXTENSION_REGISTRY_H_INCLUDED
#define EXTENSION_REGISTRY_H_INCLUDED

#include <core/non_copyable.h>
#include <core/extension_checker.h>
#include <core/render_context.h>

#include <cstring>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

#include <GL/gl.h>
#include <GL/glext.h>

namespace opengl_core
{
  struct registry_item
  {
  private:
    const char *m_extension;
    bool m_loaded_gl_funcs;

  public:
    explicit registry_item(const char *extension);

    const char *get_extension_name() const;

    bool get_if_loaded_funcs() const;

    void set_if_loaded_funcs(bool did_load);

    friend bool operator==(const registry_item &lhs, const registry_item &rhs)
    {
      return (strcmp(lhs.m_extension, rhs.m_extension) == 0);
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
      const std::string s(i.get_extension_name());
      size_t hash = 0;
      size_t offset = 'a' - 1;
      for(string::const_iterator it = s.begin(); it != s.end(); ++it) {
        hash = hash << 1 | (*it - offset);
      }
      return hash;
    }
  };
}

namespace opengl_core
{
  class extension_registry : public non_copyable
  {
  private:
    typedef bool (*load_func)();
    load_func m_func;

    std::unordered_map<registry_item, load_func> m_table;

  public:
    void init();

    bool has_extension_loaded(const char *extension) const;

    bool load_extension(const char *extension);
  };
}

extern PFNGLDRAWARRAYSINSTANCEDEXTPROC glDrawArraysInstanced;
extern PFNGLDRAWELEMENTSINSTANCEDEXTPROC glDrawElementsInstanced;

#endif

#ifndef SYMBOL_LOADER_H_INCLUDED
#define SYMBOL_LOADER_H_INCLUDED

#include <declspec.h>

#include <core/non_copyable.h>

#include <iostream>


namespace opengl_core
{
  class symbol_loader : public non_copyable
  {
  private:
    void *m_handle;
    const char *m_lib_name;
    bool m_good;

  public:
    explicit symbol_loader(const char *lib_name);
    ~symbol_loader();

    bool get_good() const { return m_good; }

    void *load(const char *symb_name);

  private:
    void print_error();
  };
}

#endif

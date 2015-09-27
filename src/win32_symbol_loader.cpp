#include "core/symbol_loader.h"

#include <Windows.h>

namespace opengl_core
{
  symbol_loader::symbol_loader(const char *lib_name) :
    m_lib_name(lib_name),
    m_good(false)
  {
    m_handle = (void*)LoadLibraryA(lib_name);

    if (!m_handle) {
      print_error();
    } else {
      m_good = true;
    }
  }

  symbol_loader::~symbol_loader()
  {
    BOOL status = FreeLibrary((HMODULE)m_handle);
    if (status) {
      print_error();
    }
  }

  void *symbol_loader::load(const char *symb_name)
  {
    void *func = nullptr;
    if (m_good) {
      func = GetProcAddress((HMODULE)m_handle, symb_name);
      if (func == nullptr) {
        std::cerr << "Failed to load " << symb_name << " from "
          << m_lib_name << std::endl;
        print_error();
      }
    }

    return func;
  }

  void symbol_loader::print_error()
  {
    DWORD err = GetLastError();
  
    std::cerr << err << std::endl;
  }
}

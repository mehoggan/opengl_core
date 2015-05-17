#include <core/symbol_loader.h>

#include <dlfcn.h>

namespace opengl_core
{
  symbol_loader::symbol_loader(const char *lib_name) :
    m_lib_name(lib_name),
    m_good(false)
  {
    m_handle = dlopen(lib_name, RTLD_GLOBAL | RTLD_LAZY);

    if (!m_handle) {
      print_error();
    } else {
      m_good = true;
    }
  }

  symbol_loader::~symbol_loader()
  {
    int status = dlclose(m_handle);
    if (status) {
      print_error();
    }
  }

  void *symbol_loader::load(const char *symb_name)
  {
    void *func = nullptr;
    if (m_good) {
      func = dlsym(m_handle, symb_name);
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
    const char *errstr = dlerror();
    std::cerr << errstr << std::endl;
  }
}

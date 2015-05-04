#include <core/extension_registry.h>

#include <iostream>
#include <iterator>

namespace opengl_core
{
  registry_item::registry_item(GLshort major, GLshort minor) :
    m_major_minor(std::make_pair(major, minor))
  {}
}

namespace opengl_core
{
  std::ostream &operator<<(std::ostream &out, const registry_item &d)
  {
    out << d.m_major_minor.first << "." << d.m_major_minor.second << std::endl
      << "\t Extensions: ";
    std::copy(d.m_extensions.begin(), d.m_extensions.end(),
      std::ostream_iterator<std::string>(out, " "));
    out << std::endl;
  }

  void extension_registry::init()
  {
    m_table.insert(registry_item(4, 5));
    m_table.insert(registry_item(4, 4));
    m_table.insert(registry_item(4, 3));
    m_table.insert(registry_item(4, 2));
    m_table.insert(registry_item(4, 1));
    m_table.insert(registry_item(4, 0));
    m_table.insert(registry_item(3, 3));
    m_table.insert(registry_item(3, 2));
    m_table.insert(registry_item(3, 1));
    m_table.insert(registry_item(3, 0));
    m_table.insert(registry_item(2, 1));
    m_table.insert(registry_item(2, 0));
    m_table.insert(registry_item(1, 5));
    m_table.insert(registry_item(1, 4));
    m_table.insert(registry_item(1, 3));
    m_table.insert(registry_item(1, 2));

    std::copy(m_table.begin(), m_table.end(),
      std::ostream_iterator<registry_item>(std::cout, ""));
  }
}

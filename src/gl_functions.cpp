#include <core/gl_functions.h>

#include <iostream>

namespace opengl_core
{
  void configure_gl_functions(int major, int minor)
  {
    const GLubyte *extensions = glGetString(GL_EXTENSIONS);
    std::cout << "GL_EXTENSIONS String = " << extensions << std::endl;
  }
}

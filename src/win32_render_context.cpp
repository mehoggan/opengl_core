#include <core/render_context.h>

#include <core/extension_checker.h>

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <utility>

#include <Windows.h>
#include <GL/gl.h>

namespace opengl_core
{
  struct render_context::context_impl
  {
    HGLRC m_context;
    GLint m_major;
    GLint m_minor;

    context_impl() :
      m_context(0),
      m_major(-1),
      m_minor(-1)
    {}
  };

  render_context::render_context() :
    m_impl(new render_context::context_impl)
  {}

  render_context::~render_context()
  {
    delete m_impl;
  }

  void render_context::init(render_window &window, fb_config &fbc)
  {
      GLint versions[][2] = {
        {4, 5}, {4, 4}, {4, 3}, {4, 2}, {4, 1}, {4, 0},
        {3, 3}, {3, 2}, {3, 1}, {3, 0},
        {2, 1}, {2, 0},
        {1, 5}, {1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0}};

      unsigned int count = sizeof(versions) / (2 * sizeof(GLint));
      unsigned int i = 0;
      for (; i < count; ++i) {
        GLint major = versions[i][0];
        GLint minor = versions[i][1];
      }
  }

  void render_context::make_current(render_window &window)
  {
  }

  void render_context::make_not_current()
  {
  }

  void render_context::destroy()
  {
    if (m_impl->m_context) {
    }
  }

  void *render_context::impl()
  {
    return (void*)m_impl->m_context;
  }

  int render_context::query_major_version() const
  {
    return m_impl->m_major;
  }

  int render_context::query_minor_version() const
  {
    return m_impl->m_minor;
  }
}

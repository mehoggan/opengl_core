#ifndef RENDER_CONTEXT_H_INCLUDED
#define RENDER_CONTEXT_H_INCLUDED

#include "opengl_core/core/non_copyable.h"

#include "opengl_core/core/fb_config.h"
#include "opengl_core/core/render_window.h"

#include <memory>

namespace opengl_core
{
  class render_context : public non_copyable
  {
  private:
    struct context_impl;
    context_impl *m_impl;

  public:
    render_context();
    ~render_context();

    void init(render_system &system, render_window &window, fb_config &fbc);
    void make_current(render_window &window);
    void make_not_current();
    void destroy();

    void *impl();

    int query_major_version() const;
    int query_minor_version() const;
  };
}


#endif

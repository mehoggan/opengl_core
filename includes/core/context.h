#ifndef OPENGL_CORE_CONTEXT_H_INCLUDED
#define OPENGL_CORE_CONTEXT_H_INCLUDED

namespace opengl_core
{
  class context
  {
  private:
    typedef void* context_t;
    typedef void* window;

    context_t m_context;

  public:
    gl_context();

    void make_current();
  };
}

#endif

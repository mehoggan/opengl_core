#import "opengl_core/core/cocoa/cocoa_render_context_objcxx.h"

@implementation render_context_objcxx

namespace opengl_core
{
  struct render_context::context_impl
  {
    void *id_self;
  };

  render_context::render_context() :
    m_impl(new context_impl)
  {
    m_impl->id_self = [[render_context_objcxx alloc] init];
  }

  render_context::~render_context()
  {
    [(id)m_impl->id_self dealloc];
  }

  void render_context::init_render_context(render_system &system,
    render_window &window, fb_config &fbc)
  {
    [(id)m_impl->id_self init_render_context:(void *)&system
      :(void *)&window :(void *)&fbc];
  }

  void render_context::make_current(render_window &window)
  {
    [(id)m_impl->id_self make_current:(void *)&window];
  }

  void render_context::make_not_current()
  {
    [(id)m_impl->id_self make_not_current];
  }

  void render_context::destroy()
  {
    [(id)m_impl->id_self destroy];
  }

  int render_context::query_major_version() const
  {
    return [(id)m_impl->id_self query_major_version];
  }

  int render_context::query_minor_version() const
  {
    return [(id)m_impl->id_self query_minor_version];
  }
}

-(void) init_render_context:(void *)system :(void *)window
    :(void *)fbc
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

-(void) make_current:(void *)window
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

-(void) make_not_current
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

-(void) destroy
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

-(int) query_major_version
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
  return 0;
}

-(int) query_minor_version
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
  return 0;
}

@end

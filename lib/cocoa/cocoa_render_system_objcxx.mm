#import "opengl_core/core/cocoa/cocoa_render_system_objcxx.h"

@implementation render_system_objcxx

namespace opengl_core
{
  struct render_system::render_system_impl
  {
    void *id_self;
  };

  render_system::render_system() :
    m_impl(new render_system_impl)
  {
    m_impl->id_self = [[render_system_objcxx alloc] init];
  }

  render_system::~render_system()
  {
    [(id)m_impl->id_self dealloc];
    delete m_impl;
  }

  void render_system::render_loop()
  {
    [(id)m_impl->id_self render_loop];
  }

  bool render_system::init_system()
  {
    bool ret;

    ret = [(id)m_impl->id_self init_system];

    render_loop();

    return ret;
  }

  void render_system::terminate()
  {
    [(id)m_impl->id_self terminate];
  }

  void render_system::destroy()
  {
    [(id)m_impl->id_self destroy];
  }
}

-(void) render_loop
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

-(bool) init_system
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
  return true;
}

-(void) terminate
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

-(void) destroy
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

@end

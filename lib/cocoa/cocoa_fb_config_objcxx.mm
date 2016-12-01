#import "opengl_core/core/cocoa/cocoa_fb_config_objcxx.h"

@implementation fb_config_objcxx

namespace opengl_core
{
  struct fb_config::fb_config_impl
  {
    void *id_self;
  };

  fb_config::fb_config() :
    m_impl(new fb_config_impl)
  {
    m_impl->id_self = [[fb_config_objcxx alloc] init];
  }

  fb_config::~fb_config()
  {
    [(id)m_impl->id_self dealloc];
    delete m_impl;
  }

  void fb_config::choose_best(render_system &system,
    render_window *detail)
  {
    [(id)m_impl->id_self choose_best:(void *)&system :(void *)detail];
  }

  void fb_config::destroy()
  {
    [(id)m_impl->id_self destory];
  }
}

-(void) choose_best:(void *)system :(void *)window
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

-(void) destory
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

@end

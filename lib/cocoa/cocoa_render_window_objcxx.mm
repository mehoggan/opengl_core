#import "opengl_core/core/cocoa/cocoa_render_window_objcxx.h"

@implementation render_window_objcxx

namespace opengl_core
{
  struct render_window::window_impl
  {
    void *id_self;
  };

  render_window::render_window() :
    m_impl(new window_impl)
  {
    m_impl->id_self = [[render_window_objcxx alloc] init];
  }

  render_window::~render_window()
  {
    [(id)m_impl->id_self dealloc];
    delete m_impl;
  }

  void render_window::init_window(render_system &system, fb_config &fbc)
  {
    [(id)m_impl->id_self init_window:(void*)&system :(void *)&fbc];
  }

  void render_window::map()
  {
    [(id)m_impl->id_self map];
  }

  void render_window::destroy()
  {
    [(id)m_impl->id_self destroy];
  }
}

-(void) init_window:(void *)system :(void *)fbc
{
  window_style = NSTitledWindowMask | NSClosableWindowMask |
    NSResizableWindowMask;

  pool = [[NSAutoreleasePool alloc] init];

  window = [[NSWindow alloc]
    initWithContentRect:NSMakeRect(100, 100, 400, 400)
    styleMask:window_style
    backing:NSBackingStoreBuffered
    defer:YES];
  [window autorelease];
}

-(void) map
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

-(void) destroy
{
  [pool drain];
}

-(void *) impl
{
  return (void *)self->window;
}

@end

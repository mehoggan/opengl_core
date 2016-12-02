#import "opengl_core/core/cocoa/cocoa_render_system_objcxx.h"

#include "opengl_core/core/fb_config.h"
#include "opengl_core/core/gl_functions.h"
#include "opengl_core/core/render_context.h"

@implementation render_system_objcxx

namespace opengl_core
{
  struct render_system::render_system_impl
  {
    void *id_self;
    render_window m_window;
    fb_config m_fbc;
    render_context m_context;
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

    m_impl->m_fbc.choose_best((*this));

    m_impl->m_window.init_window((*this), m_impl->m_fbc);

    m_impl->m_window.map();

    m_impl->m_context.init_render_context((*this), m_impl->m_window,
      m_impl->m_fbc);
    m_impl->m_context.make_current(m_impl->m_window);

    gl_functions::configure(m_impl->m_context);
    m_impl->m_context.make_not_current();

    render_loop();

    return ret;
  }

  void render_system::terminate_system()
  {
    [(id)m_impl->id_self terminate_system];
  }

  void render_system::destroy()
  {
    m_impl->m_context.make_not_current();
    m_impl->m_context.destroy();
    m_impl->m_window.destroy();
    m_impl->m_fbc.destroy();
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

  pool = [[NSAutoreleasePool alloc] init];
  [NSApplication sharedApplication];

  window_style = NSTitledWindowMask | NSClosableWindowMask |
    NSResizableWindowMask;

  window_rect = NSMakeRect(100, 100, 400, 400);
  window = [[NSWindow alloc] initWithContentRect:window_rect
    styleMask:window_style
    backing:NSBackingStoreBuffered
    defer:NO];
  [window autorelease];

  window_controller = [[NSWindowController alloc] initWithWindow:window];
  [window_controller autorelease];

  [window orderFrontRegardless];
  [NSApp run];

  [pool drain];

  return true;
}

-(void) terminate_system
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

-(void) destroy
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

@end

#import "opengl_core/core/cocoa/cocoa_gl_functions_objcxx.h"

#include "opengl_core/core/symbol_loader.h"

#include <functional>
#include <utility>
#include <vector>

@implementation gl_functions_objcxx

namespace opengl_core
{
  void gl_functions::configure(const opengl_core::render_context &context)
  {
    [gl_functions_objcxx configure:(void *)&context];

    symbol_loader sym_loader("libGL.dylib");
    /*assert(sym_loader.get_good() && "Failed to load libGL.dylib");*/

    typedef std::function<void(symbol_loader *)> load_func;
    std::pair<std::vector<int>, load_func> versions[] =
    {
      std::make_pair<std::vector<int>, load_func>({3, 0}, std::bind(
        &opengl_core::gl_functions::load_3_0, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({2, 1}, std::bind(
        &opengl_core::gl_functions::load_2_1, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({2, 0}, std::bind(
        &opengl_core::gl_functions::load_2_0, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({1, 5}, std::bind(
        &opengl_core::gl_functions::load_1_5, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({1, 4}, std::bind(
        &opengl_core::gl_functions::load_1_4, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({1, 3}, std::bind(
        &opengl_core::gl_functions::load_1_3, &sym_loader)),
      std::make_pair<std::vector<int>, load_func>({1, 2}, std::bind(
        &opengl_core::gl_functions::load_1_2, &sym_loader))
    };
    for (auto version : versions) {
      if (version.first[0] <= context.query_major_version() &&
        version.first[1] <= context.query_minor_version()) {
        version.second(&sym_loader);
      }
    }
  }

  void gl_functions::load_1_2(symbol_loader *sym_loader)
  {
    [gl_functions_objcxx load_1_2:(void *)sym_loader];
  }

  void gl_functions::load_1_3(symbol_loader *sym_loader)
  {
    [gl_functions_objcxx load_1_3:(void *)sym_loader];
  }

  void gl_functions::load_1_4(symbol_loader *sym_loader)
  {
    [gl_functions_objcxx load_1_4:(void *)sym_loader];
  }

  void gl_functions::load_1_5(symbol_loader *sym_loader)
  {
    [gl_functions_objcxx load_1_5:(void *)sym_loader];
  }

  void gl_functions::load_2_0(symbol_loader *sym_loader)
  {
    [gl_functions_objcxx load_2_0:(void *)sym_loader];
  }

  void gl_functions::load_2_1(symbol_loader *sym_loader)
  {
    [gl_functions_objcxx load_2_1:(void *)sym_loader];
  }

  void gl_functions::load_3_0(symbol_loader *sym_loader)
  {
    [gl_functions_objcxx load_3_0:(void *)sym_loader];
  }
}

+(void) configure:(void *) context
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

+(void) load_1_2:(void *) sym_loader
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

+(void) load_1_3:(void *) sym_loader
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

+(void) load_1_4:(void *) sym_loader
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

+(void) load_1_5:(void *) sym_loader
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

+(void) load_2_0:(void *) sym_loader
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

+(void) load_2_1:(void *) sym_loader
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

+(void) load_3_0:(void *) sym_loader
{
  NSLog(@"Hello World %s\n", __FUNCTION__);
}

@end

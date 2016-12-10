#include "opengl_core/core/render_system.h"
#include "opengl_core/core/x11/x11_gl_functions.h"

#include "suite.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

#include <check.h>

void init_function(opengl_core::render_system &system)
{
  std::cout << "Init" << std::endl;
}

void pre_render_function(opengl_core::render_system &system)
{
}

void render_function(opengl_core::render_system &system, std::size_t millis)
{
}

void post_render_function(opengl_core::render_system &system)
{
}

void shutdown_function(opengl_core::render_system &system)
{
  std::cout << "Shutdown" << std::endl;
}

START_TEST(test_x11_render_system)
{
  opengl_core::render_system::init_function init = std::bind(
    &init_function, std::placeholders::_1);
  opengl_core::render_system::pre_render_function pre = std::bind(
    &pre_render_function, std::placeholders::_1);
  opengl_core::render_system::render_function renderer = std::bind(
    &render_function, std::placeholders::_1, std::placeholders::_2);
  opengl_core::render_system::post_render_function post = std::bind(
    &post_render_function, std::placeholders::_1);
  opengl_core::render_system::shutdown_function shutdown = std::bind(
    &shutdown_function, std::placeholders::_1);

  opengl_core::render_system render_system(init, pre, renderer, post,
    shutdown, false);
  ck_assert(render_system.init_system());
  render_system.destroy();
}
END_TEST

int
main(int argc, char *argv[])
{
  Suite *s;
  SRunner *sr;
  TCase *tc;
  int result;

  s = suite_create("Unit Tests");
  tc = tcase_create(__FILE__);

  tcase_add_test(tc, test_x11_render_system);

  suite_add_tcase(s, tc);
  sr = suite_runner_create(s);
  result = (run_and_report(sr) == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
  return result;
}

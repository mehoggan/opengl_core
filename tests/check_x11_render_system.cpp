#include "opengl_core/core/render_system.h"
#include "opengl_core/core/x11/x11_gl_functions.h"

#include "suite.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

#include <check.h>

void render_function(std::size_t millis)
{
  ck_assert(true);
}

START_TEST(test_x11_render_system)
{
  opengl_core::render_system::render_function renderer = std::bind(
    &render_function, std::placeholders::_1);
  opengl_core::render_system render_system(renderer);
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

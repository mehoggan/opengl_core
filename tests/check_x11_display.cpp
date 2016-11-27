#include "opengl_core/core/x11/x11_display.h"

#include "suite.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include <check.h>

void acquire_display1_hold_m()
{
  Display *&d = opengl_core::x11_display::acquire();
  std::cout << "Address of display on thread " << std::this_thread::get_id()
    << " is " << &d << std::endl;
  ck_assert(d && opengl_core::x11_display::use_count() == 1);
  opengl_core::x11_display::sync();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  opengl_core::x11_display::release();
  ck_assert(!d && opengl_core::x11_display::use_count() == 0);
}

START_TEST(test_x11_display)
{
  Display *&d = opengl_core::x11_display::acquire();
  ck_assert(d && opengl_core::x11_display::use_count() == 1);

  std::cout << "Address of display on thread " << std::this_thread::get_id()
    << " is " << &d << std::endl;

  std::thread test_0(acquire_display1_hold_m);

  ck_assert(d && opengl_core::x11_display::use_count() == 1);

  for (unsigned int i = 0; i < 4; ++i) {
    Display *&di = opengl_core::x11_display::acquire();
    (void)di;
    ck_assert(d && opengl_core::x11_display::use_count() == 2);
    opengl_core::x11_display::sync();
    opengl_core::x11_display::release();
    opengl_core::x11_display::sync();
    ck_assert(d && opengl_core::x11_display::use_count() == 1);
  }

  ck_assert(d && opengl_core::x11_display::use_count() == 1);

  opengl_core::x11_display::release();

  ck_assert(!d && opengl_core::x11_display::use_count() == 0);

  std::cout << "Waiting on thread to join" << std::endl;
  test_0.join();

  ck_assert(!d && opengl_core::x11_display::use_count() == 0);
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

  tcase_add_test(tc, test_x11_display);

  suite_add_tcase(s, tc);
  sr = suite_runner_create(s);
  result = (run_and_report(sr) == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
  return result;
}

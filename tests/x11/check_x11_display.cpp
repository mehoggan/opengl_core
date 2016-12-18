#include "opengl_core/core/x11/x11_display.h"

#include "suite.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <check.h>

void acquire_display1_hold_m()
{
  std::uint32_t use = 0;

  opengl_core::x11_display_thread_specific_acquire();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(1, use);
  opengl_core::x11_display_thread_specific_release();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(0, use);

  opengl_core::x11_display_thread_specific_acquire();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(1, use);
  opengl_core::x11_display_thread_specific_release();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(0, use);

  opengl_core::x11_display_thread_specific_acquire();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(1, use);
  opengl_core::x11_display_thread_specific_release();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(0, use);

  opengl_core::x11_display_thread_specific_acquire();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(1, use);
  opengl_core::x11_display_thread_specific_release();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(0, use);

  opengl_core::x11_display_thread_specific_acquire();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(1, use);
  opengl_core::x11_display_thread_specific_release();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(0, use);

  opengl_core::x11_display_thread_specific_acquire();
  opengl_core::x11_display_thread_specific_acquire();
  opengl_core::x11_display_thread_specific_acquire();
  opengl_core::x11_display_thread_specific_acquire();
  opengl_core::x11_display_thread_specific_acquire();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(5, use);
  opengl_core::x11_display_thread_specific_release();
  opengl_core::x11_display_thread_specific_release();
  opengl_core::x11_display_thread_specific_release();
  opengl_core::x11_display_thread_specific_release();
  opengl_core::x11_display_thread_specific_release();
  use = opengl_core::x11_display_thread_specifc_use_count();
  ck_assert_int_eq(0, use);
}

START_TEST(test_x11_display)
{
  std::vector<std::thread> threads;
  opengl_core::x11_display_init();
  for (unsigned short i = 0; i < 9; ++i) {
    threads.push_back(std::thread(std::bind(&acquire_display1_hold_m)));
    threads.back().join(); /* Cleaner to join here for helgrind. */
  }
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

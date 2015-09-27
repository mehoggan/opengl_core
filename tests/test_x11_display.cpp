#include "test_x11_display.h"

#include <chrono>
#include <iostream>
#include <thread>

void acquire_display1_hold_m()
{
  Display *&d = opengl_core::x11_display::acquire();
  std::cout << "Address of display on thread " << std::this_thread::get_id()
    << " is " << &d << std::endl;
  OPENGL_CORE_ASSERT(d && opengl_core::x11_display::use_count() == 1);
  opengl_core::x11_display::sync();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  opengl_core::x11_display::release();
  OPENGL_CORE_ASSERT(!d && opengl_core::x11_display::use_count() == 0);
}

bool test_x11_display::run()
{
  Display *&d = opengl_core::x11_display::acquire();
  OPENGL_CORE_ASSERT(d && opengl_core::x11_display::use_count() == 1);

  std::cout << "Address of display on thread " << std::this_thread::get_id()
    << " is " << &d << std::endl;

  std::thread test_0(acquire_display1_hold_m);

  OPENGL_CORE_ASSERT(d && opengl_core::x11_display::use_count() == 1);

  for (unsigned int i = 0; i < 4; ++i) {
    Display *&di = opengl_core::x11_display::acquire();
    OPENGL_CORE_ASSERT(d && opengl_core::x11_display::use_count() == 2);
    opengl_core::x11_display::sync();
    opengl_core::x11_display::release();
    opengl_core::x11_display::sync();
    OPENGL_CORE_ASSERT(d && opengl_core::x11_display::use_count() == 1);
  }

  OPENGL_CORE_ASSERT(d && opengl_core::x11_display::use_count() == 1);

  opengl_core::x11_display::release();

  OPENGL_CORE_ASSERT(!d && opengl_core::x11_display::use_count() == 0);

  std::cout << "Waiting on thread to join" << std::endl;
  test_0.join();

  OPENGL_CORE_ASSERT(!d && opengl_core::x11_display::use_count() == 0);
  return true;
}

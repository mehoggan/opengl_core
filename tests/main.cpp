#include <core/x11_display.h>

#include <cassert>
#include <chrono>
#include <iostream>
#include <system_error>
#include <thread>

void acquire_display1_hold_m()
{
  Display *&d = opengl_core::x11_display::acquire();
  assert(d && opengl_core::x11_display::use_count() == 1);
  opengl_core::x11_display::sync();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  opengl_core::x11_display::release();
  assert(!d && opengl_core::x11_display::use_count() == 0);
}

int main(int argc, char *argv[])
{
  XInitThreads();

  Display *&d = opengl_core::x11_display::acquire();
  assert(d && opengl_core::x11_display::use_count() == 1);

  std::thread test_0(acquire_display1_hold_m);

  assert(d && opengl_core::x11_display::use_count() == 1);

  for (unsigned int i = 0; i < 4; ++i) {
    Display *&di = opengl_core::x11_display::acquire();
    assert(d && opengl_core::x11_display::use_count() == 2);
    opengl_core::x11_display::sync();
    opengl_core::x11_display::release();
    opengl_core::x11_display::sync();
    assert(d && opengl_core::x11_display::use_count() == 1);
  }

  assert(d && opengl_core::x11_display::use_count() == 1);

  opengl_core::x11_display::release();

  assert(!d && opengl_core::x11_display::use_count() == 0);

  std::cout << "Waiting on thread to join" << std::endl;
  test_0.join();

  assert(!d && opengl_core::x11_display::use_count() == 0);

  return 0;
}

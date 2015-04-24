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
  std::this_thread::sleep_for(std::chrono::seconds(5));
  opengl_core::x11_display::sync();
  opengl_core::x11_display::release();
  assert(!d && opengl_core::x11_display::use_count() == 0);
}

int main(int argc, char *argv[])
{
  XInitThreads();

  std::thread test_0(acquire_display1_hold_m);

  Display *&d = opengl_core::x11_display::acquire();
  assert(d && opengl_core::x11_display::use_count() == 1);

  for (unsigned int i = 0; i < 4; ++i) {
    Display *&di = opengl_core::x11_display::acquire();
    assert(di == d && "On a given thread all displays should be the same");
    assert(di && opengl_core::x11_display::use_count() == 2 && (i + 1));
    opengl_core::x11_display::sync();
    opengl_core::x11_display::release();
    // Because the display is still alive we can sync after release
    opengl_core::x11_display::sync();
    assert(di && opengl_core::x11_display::use_count() == 1 && (i + 1));
  }

  opengl_core::x11_display::release();
  assert(!d && opengl_core::x11_display::use_count() == 0);

  std::cout << "Waiting on thread to join" << std::endl;
  test_0.join();

  return 0;
}

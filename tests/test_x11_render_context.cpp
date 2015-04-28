#include <test_render_context.h>

#include <core/fb_config.h>
#include <core/render_context.h>
#include <core/render_window.h>
#include <core/x11_display.h>

#include <chrono>
#include <thread>

bool test_render_context::run()
{
  opengl_core::x11_display::acquire();

  opengl_core::fb_config fbc;
  fbc.choose_best();

  opengl_core::render_window window;
  window.init(fbc);
  window.map();

  opengl_core::render_context context;
  context.init(window, fbc, 2, 0);

  context.make_current(window);

  auto start = std::chrono::high_resolution_clock::now();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << "Mapped window with Context and Waited " << elapsed.count()
    << " ms\n";

  context.make_not_current();

  context.destroy();
  window.destroy();

  opengl_core::x11_display::release();
}

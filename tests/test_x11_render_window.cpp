#include <test_render_window.h>

#include <core/fb_config.h>
#include <core/render_window.h>

#include <chrono>
#include <thread>

bool test_render_window::run()
{
  opengl_core::fb_config fbc;
  fbc.choose_best(2, 0);

  opengl_core::render_window window;
  window.init(fbc);
  window.map();

  auto start = std::chrono::high_resolution_clock::now();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << "Mapped window and Waited " << elapsed.count() << " ms\n";

  window.destroy();
}

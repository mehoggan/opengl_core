#include <test_render_context.h>

#include <core/fb_config.h>
#include <core/render_context.h>
#include <core/render_window.h>

#include <chrono>
#include <sstream>
#include <thread>

#include <Windows.h>

bool test_render_context::run()
{
  opengl_core::render_window window;
  opengl_core::fb_config fbc;
  opengl_core::render_context context;
  context.init(window, fbc);
  context.make_current(window);
  window.map();

  auto start = std::chrono::high_resolution_clock::now();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;

  std::stringstream ss;
  ss << "Mapped window with Context and Waited ";
  ss << elapsed.count();
  ss << " ms" << std::endl;
  OutputDebugStringA(ss.str().c_str());

  context.make_not_current();
  context.destroy();
  window.destroy();

  return true;
}

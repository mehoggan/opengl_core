#include "opengl_core/core/draw_buffer_config.h"
#include "opengl_core/core/draw_buffer_context.h"
#include "opengl_core/core/draw_buffer_window.h"
#include "opengl_core/core/init.h"
#include "opengl_core/core/standard_renderer.h"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

void thread_func(int x, int y, int w, int h, int gl_major, int gl_minor);

int main(int argc, char * argv[])
{
  bool init_status = opengl_core::init();
  if (!init_status) {
    std::cerr << "Failed to init all systems." << std::endl << std::flush;
    exit(-1);
  }

  std::vector<std::thread> threads;
  threads.resize(2);
  for (int i = 0; i < threads.size(); ++i) {
    threads[i] = std::thread(std::bind(&thread_func, std::rand() % 100,
      std::rand() % 100, 800, 600, 2, 1));
  }

  for (auto &thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

void thread_func(int x, int y, int w, int h, int gl_major, int gl_minor)
{
  opengl_core::draw_buffer_config fbc =
    opengl_core::choose_best_draw_buffer_config();
  opengl_core::draw_buffer_window win =
    opengl_core::draw_buffer_window_create(fbc, x, y, w, h);
  opengl_core::draw_buffer_window_show(win);
  opengl_core::draw_buffer_context ctx =
    opengl_core::draw_buffer_context_create(fbc, gl_major, gl_minor);
  opengl_core::draw_buffer_config_free(fbc);

  opengl_core::standard_event_loop_run(win, ctx);

  opengl_core::draw_buffer_context_free(ctx);
  opengl_core::draw_buffer_window_free(win);
}

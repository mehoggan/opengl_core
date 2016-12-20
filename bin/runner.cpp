#include "opengl_core/core/x11/x11_display.h"
#include "opengl_core/core/draw_buffer_config.h"
#include "opengl_core/core/draw_buffer_context.h"
#include "opengl_core/core/draw_buffer_window.h"
#include "opengl_core/core/init.h"
#include "opengl_core/core/platform.h"

#include <GL/gl.h>
#include <GL/glx.h>

#include <cstdlib>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void thread_func(int x, int y, int w = 800, int h = 600);

void draw_quad()
{
  glBegin(GL_QUADS);
    glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
    glColor3f(0., 1., 0.); glVertex3f(.75, -.75, 0.);
    glColor3f(0., 0., 1.); glVertex3f(.75,  .75, 0.);
    glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
  glEnd();
}

int main (int argc, char ** argv)
{
  bool init_status = opengl_core::init();
  if (!init_status) {
    std::cerr << "Failed to init all systems." << std::endl << std::flush;
    exit(-1);
  }

  std::vector<std::thread> threads;
  threads.resize(10);
  for (int i = 0; i < 9; ++i) {
    threads[i] = std::thread(std::bind(&thread_func, std::rand() % 100,
      std::rand() % 100, 800, 600));
  }

  for (auto &thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

void thread_func(int x, int y, int w, int h)
{
  opengl_core::draw_buffer_config *fbc =
    opengl_core::choose_best_draw_buffer_config();
  if (!fbc) {
    std::cerr << "Failed to retrieve a framebuffer config" << std::endl;
    exit(-1);
  }

  opengl_core::draw_buffer_window win =
    opengl_core::draw_buffer_window_create(*fbc, x, y, w, h);
  opengl_core::draw_buffer_window_show(win);

  opengl_core::draw_buffer_context ctx =
    opengl_core::draw_buffer_context_create(*fbc, 3, 0);

  opengl_core::draw_buffer_config_free(fbc);

  opengl_core::draw_buffer_context_make_current(ctx, win);
    glViewport(0, 0, 800, 600);
    glClearColor (0, 0.5, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_quad();
    opengl_core::swap_buffers(win);

    sleep(5);

    glClearColor (1, 0.5, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_quad();
    opengl_core::swap_buffers(win);

    sleep(5);

  ctx = opengl_core::draw_buffer_context_get_current();
  opengl_core::draw_buffer_context_make_not_current(ctx);
  opengl_core::draw_buffer_context_free(ctx);

  opengl_core::draw_buffer_window_free(win);
}

#include "opengl_core/core/draw_buffer_config.h"
#include "opengl_core/core/draw_buffer_context.h"
#include "opengl_core/core/draw_buffer_window.h"
#include "opengl_core/core/init.h"
#include "opengl_core/core/standard_renderer.h"
#include "opengl_core/core/x11/x11_gl_functions.h"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

int major = 3;
int minor = 2;

void dummy(int x, int y, int w, int h, int gl_major, int gl_minor)
{
}

void thread_func(int x, int y, int w, int h, int gl_major, int gl_minor);

int main(int argc, char * argv[])
{
  bool init_status = opengl_core::init();
  if (!init_status) {
    std::cerr << "Failed to init all systems." << std::endl << std::flush;
    exit(-1);
  }

  std::vector<std::thread> threads;
  threads.resize(1);
  for (int i = 0; i < threads.size(); ++i) {
    threads[i] = std::thread(std::bind(&dummy, std::rand() % 100,
      std::rand() % 100, 800, 600, major, minor));
  }

  for (auto &thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
  thread_func(20, 20, 800, 600, major, minor);
}

void init();
void pre_render();
void render();
void post_render();
void close();

void thread_func(int x, int y, int w, int h, int gl_major, int gl_minor)
{
  opengl_core::draw_buffer_config fbc =
    opengl_core::choose_best_draw_buffer_config();
  opengl_core::draw_buffer_window win =
    opengl_core::draw_buffer_window_create(fbc, x, y, w, h);
  opengl_core::draw_buffer_window_show(win);
  opengl_core::draw_buffer_context ctx =
    opengl_core::draw_buffer_context_create(fbc, gl_major, gl_minor);

  opengl_core::set_thread_local_init_callback(
    std::bind(&init));
  opengl_core::set_thread_local_pre_render_callback(
    std::bind(&pre_render));
  opengl_core::set_thread_local_render_callback(
    std::bind(&render));
  opengl_core::set_thread_local_post_render_callback(
    std::bind(&post_render));
  opengl_core::set_thread_local_close_callback(
    std::bind(&close));

  opengl_core::draw_buffer_context_make_current(ctx, win);
  opengl_core::gl_functions::configure(gl_major, gl_minor);
  opengl_core::draw_buffer_context_make_not_current(ctx);

  opengl_core::standard_event_loop_run(win, ctx);

  opengl_core::draw_buffer_context_free(ctx);
  opengl_core::draw_buffer_window_free(win);
  opengl_core::draw_buffer_config_free(fbc);
}

void init()
{
}

void pre_render()
{
}

void render()
{
  glViewport(0, 0, 800, 600);
  glClearColor (0, 0.5, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBegin(GL_QUADS);
  {
    glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
    glColor3f(0., 1., 0.); glVertex3f(.75, -.75, 0.);
    glColor3f(0., 0., 1.); glVertex3f(.75,  .75, 0.);
    glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
  }
  glEnd();
}

void post_render()
{
}

void close()
{
}

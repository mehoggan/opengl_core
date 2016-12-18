#include "opengl_core/core/x11/x11_display.h"
#include "opengl_core/core/init.h"

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

#define GLX_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB     0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig,
  GLXContext, Bool, const int*);

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
  Display *display = opengl_core::x11_display_thread_specific_acquire();
  if (!display) {
    std::cerr << "Failed to acquire thread on " << std::this_thread::get_id()
      << std::endl << std::flush;
  }

  glXCreateContextAttribsARBProc glXCreateContextAttribsARB = NULL;

  const char *extensions = glXQueryExtensionsString(display,
    DefaultScreen(display));
  std::cout << extensions << std::endl;

  static int visual_attribs[] =
  {
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_DOUBLEBUFFER, true,
    GLX_RED_SIZE, 1,
    GLX_GREEN_SIZE, 1,
    GLX_BLUE_SIZE, 1,
    None
  };

  std::cout << "Getting framebuffer config" << std::endl;
  int fbcount;
  GLXFBConfig *fbc = glXChooseFBConfig(display, DefaultScreen(display),
    visual_attribs, &fbcount);
  if (!fbc) {
    std::cerr << "Failed to retrieve a framebuffer config" << std::endl;
    exit(-1);
  }

  std::cout << "Getting XVisualInfo" << std::endl;
  XVisualInfo *vi = glXGetVisualFromFBConfig(display, fbc[0]);

  XSetWindowAttributes swa;
  std::cout << "Creating colormap" << std::endl;
  swa.colormap = XCreateColormap(display, RootWindow(display, vi->screen),
    vi->visual, AllocNone);
  swa.border_pixel = 0;
  swa.event_mask = StructureNotifyMask;

  std::cout << "Creating window" << std::endl;
  Window win = XCreateWindow(display, RootWindow(display, vi->screen), x, y,
    w, h, 0, vi->depth, InputOutput, vi->visual,
    CWBorderPixel | CWColormap | CWEventMask, &swa);
  if (!win) {
    std::cerr << "Failed to create window." << std::endl << std::flush;
    exit(-1);
  }

  std::cout << "Mapping window" << std::endl;
  XMapWindow(display, win);

  // Create an oldstyle context first, to get the correct function pointer
  // for glXCreateContextAttribsARB
  GLXContext ctx_old = glXCreateContext(display, vi, 0, GL_TRUE);
  glXCreateContextAttribsARB =  (glXCreateContextAttribsARBProc)
    glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
  glXMakeCurrent(display, 0, 0);
  glXDestroyContext(display, ctx_old);

  if (glXCreateContextAttribsARB == NULL) {
    std::cerr << "glXCreateContextAttribsARB entry point not found." <<
      std::endl << std::flush;
    exit(-1);
  }

  static int context_attribs[] =
  {
    GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
    GLX_CONTEXT_MINOR_VERSION_ARB, 0,
    None
  };

  std::cout << "Creating context" << std::endl;
  GLXContext ctx = glXCreateContextAttribsARB(display, fbc[0], NULL, true,
    context_attribs);
  if (!ctx) {
    std::cerr << "Failed to create GL3 context." << std::endl << std::flush;
    exit(-1);
  }

  std::cout << "Making context current" << std::endl;
  glXMakeCurrent(display, win, ctx);

    glViewport(0, 0, 800, 600);
    glClearColor (0, 0.5, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_quad();
    glXSwapBuffers (display, win);

    sleep(5);

    glClearColor (1, 0.5, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_quad();
    glXSwapBuffers (display, win);

    sleep(5);

  ctx = glXGetCurrentContext();
  glXMakeCurrent(display, 0, 0);
  glXDestroyContext(display, ctx);

  opengl_core::x11_display_thread_specific_release();
}

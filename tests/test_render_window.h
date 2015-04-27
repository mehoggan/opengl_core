#ifndef TEST_RENDER_WINDOW_H_INCLUDED
#define TEST_RENDER_WINDOW_H_INCLUDED

#include <test_base.h>

class test_render_window : public test_base
{
  virtual bool run();
  virtual const char *name() { return "test_render_window"; }
};

#endif

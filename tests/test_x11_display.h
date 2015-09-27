#ifndef TEST_X11_DISPLAY_H_INCLUDED
#define TEST_X11_DISPLAY_H_INCLUDED

#include "test_base.h"
#include "core/x11_display.h"

class test_x11_display : public test_base
{
  virtual bool run();
  virtual const char *name() { return "test_x11_display"; }
};

#endif

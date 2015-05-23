#ifndef TEST_WIN32_HINSTANCE_H_INCLUDED
#define TEST_WIN32_HINSTANCE_H_INCLUDED

#include <test_base.h>

class test_win32_hinstance : public test_base
{
  virtual bool run();
  virtual const char *name() { return "test_win32_hinstance"; }
};

#endif
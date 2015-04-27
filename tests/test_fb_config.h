#ifndef TEST_FB_CONFIG_H_INCLUDED
#define TEST_FB_CONFIG_H_INCLUDED

#include <test_base.h>

class test_fb_config : public test_base
{
  virtual bool run();
  virtual const char *name() { return "test_fb_config"; }
};

#endif

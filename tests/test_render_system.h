#ifndef TEST_RENDER_SYSTEM_H_INCLUDED
#define TEST_RENDER_SYSTEM_H_INCLUDED

#include "test_base.h"
#include "core/render_system.h"
#include "core/gl_functions.h"

class test_render_system : public test_base
{
  virtual bool run();
  virtual const char *name() { return "test_render_system"; }
};

#endif

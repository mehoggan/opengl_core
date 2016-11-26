#include "opengl_core/core/render_system.h"

int main(int argc, char *argv[])
{
  opengl_core::render_system render_system;
  render_system.init();
  render_system.destroy();
  return 0;
}

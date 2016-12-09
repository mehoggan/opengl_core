#include "opengl_core/core/render_system.h"

#include <iostream>

void render_function(std::size_t millis)
{
  std::cout << "Hello World" << std::endl << std::flush;
}

int main(int argc, char *argv[])
{
  opengl_core::render_system::render_function renderer = std::bind(
    &render_function, std::placeholders::_1);
  opengl_core::render_system render_system(renderer, true);
  render_system.init_system();
  render_system.destroy();
  return 0;
}

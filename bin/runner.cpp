#include "opengl_core/core/render_system.h"
#include "opengl_core/core/x11/x11_gl_functions.h"

#include <cstdint>
#include <iostream>
#include <thread>

void init_function(opengl_core::render_system &system)
{
}

void pre_render_function(opengl_core::render_system &system)
{
}

void render_function(opengl_core::render_system &system, std::size_t millis)
{
}

void post_render_function(opengl_core::render_system &system)
{
}

void shutdown_function(opengl_core::render_system &system)
{
}

int main(int argc, char *argv[])
{
/*
  opengl_core::render_system::init_function init = std::bind(
    &init_function, std::placeholders::_1);
  opengl_core::render_system::pre_render_function pre = std::bind(
    &pre_render_function, std::placeholders::_1);
  opengl_core::render_system::render_function renderer = std::bind(
    &render_function, std::placeholders::_1, std::placeholders::_2);
  opengl_core::render_system::post_render_function post = std::bind(
    &post_render_function, std::placeholders::_1);
  opengl_core::render_system::shutdown_function shutdown = std::bind(
    &shutdown_function, std::placeholders::_1);
*/

  return 0;
}

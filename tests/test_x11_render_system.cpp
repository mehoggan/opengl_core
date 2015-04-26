#include <test_render_system.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

bool test_render_system::run()
{
  opengl_core::render_system::init(1, 4);
  // If you do not destroy next test will fail.
  opengl_core::render_system::destroy();

  std::system("ldconfig -p | grep 'GL' > ldconfig.txt");
  std::fstream ldconfig("./ldconfig.txt");
  std::string line;
  while (std::getline(ldconfig, line)) {
    std::cout << line << std::endl;
  }
  std::system("rm ./ldconfig.txt");
}

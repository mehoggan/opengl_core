#include <test_base.h>
#include <test_render_system.h>

#define _CRTDBG_MAP_ALLOC
#include <core/memory_leaks.h>

#include <array>
#include <cstdint>
#include <memory>

int main(int argc, char *argv[])
{
  MEMORY_LEAK_DETECTION_START();
  std::array<std::shared_ptr<test_base>, 1> tests = {
    std::shared_ptr<test_base>(new test_render_system()),
  };

  std::cout << "Going to run " << tests.size() << " tests." << std::endl;
  for(auto test_ptr : tests) {
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "Running " << test_ptr->name() << std::endl;
    std::cout << "==============================================" << std::endl;
    test_ptr->run();
  }

  for (auto test_ptr : tests) {
    test_ptr.reset();
  }

  return 0;
}

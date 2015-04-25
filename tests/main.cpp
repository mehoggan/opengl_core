#include <test_base.h>
#include <test_x11_display.h>
#include <test_render_system.h>

#include <cstdint>
#include <memory>

#include <X11/Xlib.h>

int main(int argc, char *argv[])
{
  XInitThreads();

  std::array<std::shared_ptr<test_base>, 2> tests = {
    std::shared_ptr<test_base>(new test_render_system()),
    std::shared_ptr<test_base>(new test_x11_display())
  };

  for(std::size_t i = 0; i < tests.size(); ++i) {
    std::cout << "Running " << tests[i]->name() << std::endl;
    tests[i]->run();
  }

  return 0;
}

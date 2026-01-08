#include <iostream>
#include <cstdlib>

namespace Foo {
enum Bar : uint8_t {
  x = 0x01,
  y = 0x02,
  z = 0x04,
  AllBar = x | y | z,
};
}

int main(int argc, char **argv) {
  //Foo::Bar bits = Foo::x | Foo::y; // compile error, needs cast:
  Foo::Bar bits = (Foo::Bar)(Foo::x | Foo::y);
  Foo::Bar all = Foo::AllBar;

  if (bits & Foo::x) {
    std::cout << "x set (expected)\n";
  }
  else
  {
      abort();
  }

  if (bits == all) {
    std::cout << "all set\n";
    std::abort(); // unexpected
  }
  else
  {
    std::cout << "all not set (expected)\n";
  }

  //bits |= Foo::z; // compile error, needs cast:
  bits = (Foo::Bar)(bits | Foo::z);

  if (bits == all) {
    std::cout << "all set now\n";
  }
  else
  {
    std::abort(); // unexpected
  }

  return 0;
}

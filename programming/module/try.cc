import stuff;
#if 0
// This doesn't work.  Doens't seem to be implemented in g++-15:
import iostream;
import format;
#else
import std;
#endif

int main() {

  //stuff::helper();

  auto v = stuff::collect_lines(std::cin);
  for (const auto &i : v) {
      std::cout << std::format("{}\n", i);
  }

  return 0;
}

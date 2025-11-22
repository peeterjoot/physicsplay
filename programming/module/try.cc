import stuff;
import std;

int main() {

  //stuff::helper();

  auto v = stuff::collect_lines(std::cin);
  for (const auto &i : v) {

      // g++-15.2.1-4 breaks with use of std::format:
      //std::cout << std::format("{}\n", i);
      std::cout << i << '\n';
  }

  return 0;
}

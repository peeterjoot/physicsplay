export module stuff;
import std;

namespace stuff {

void helper() { std::cout << "call to a private function\n"; }

export
std::vector<std::string> collect_lines(std::istream &is) {

  helper();

  std::unordered_set<std::string> s;
  for (std::string line; std::getline(is, line);)
    s.insert(line);

  return std::vector{std::from_range, s};
}
} // namespace stuff

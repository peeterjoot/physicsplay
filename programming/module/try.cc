import std;

using namespace std;

vector<string> collect_lines(istream &is) {
  unordered_set<string> s;
  for (string line; getline(is, line);)
    s.insert(line);

  return vector{from_range, s};
}

int main() {
  auto v = collect_lines(cin);
  for (const auto &i : v) {
    cout << format("{}\n", i);
  }

  return 0;
}

// https://en.cppreference.com/w/cpp/utility/source_location.html (run through clang-format)
#include <iostream>
#include <source_location>
#include <string_view>

void log(const std::string_view message, const std::source_location location =
                                             std::source_location::current()) {
  std::clog << "file: " << location.file_name() << '(' << location.line() << ':'
            << location.column() << ") `" << location.function_name()
            << "`: " << message << '\n';
}

template <typename T> void fun(T x) {
  log(x); // line 14
}

int main(int, char *[]) {
  log("Hello world!"); // line 18
  fun("Hello C++20!");

  return 0;
}

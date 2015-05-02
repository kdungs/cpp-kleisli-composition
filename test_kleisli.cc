#include "kleisli.h"

#include <iostream>
#include <ostream>

#include <experimental/optional>
using std::experimental::optional;

template <typename T>
auto operator<<(std::ostream& os, const optional<T>& x) -> std::ostream & {
  if (!x) {
    os << "Nothing";
  } else {
    os << "Just " << *x;
  }
  return os;
}

int main() {
  auto f0 = [](int x) { return optional<int>{x + 1}; };
  auto f1 = [](int x) { return optional<int>{x + 10}; };
  auto f2 = [](int x) { return optional<int>{x + 100}; };
  auto g0 = [](int) { return optional<int>{}; };  // Always Nothing

  auto pipeline = Kleisli(f0, Kleisli(f1, f2));
  auto pipelineError = Kleisli(f0, Kleisli(g0, Kleisli(f1, f2)));

  auto x = Bind(optional<int>{1}, pipeline);
  auto y = Bind(optional<int>{1}, pipelineError);

  std::cout << x << '\n';
  std::cout << y << '\n';
}

#include "kleisli.h"

#include <iostream>

int main() {
  auto f0 = [](int x) { return optional<int>{x + 1}; };
  auto f1 = [](int x) { return optional<int>{x + 10}; };
  auto f2 = [](int x) { return optional<int>{x + 100}; };
  auto pipeline = Kleisli<>(f0, Kleisli<>(f1, f2));

  auto x = Bind(optional<int>{5}, pipeline);

  if (!x) {
    std::cout << "None\n";
  } else {
    std::cout << *x << '\n';
  }
}

#include <functional>
#include <iostream>

auto main() -> int {
  std::cout << "Hello, world!\n";
  std::cout << std::plus<int>{}(1, 1.23) << '\n';
  std::cout << std::plus<>{}(1, 1.23) << '\n';
}
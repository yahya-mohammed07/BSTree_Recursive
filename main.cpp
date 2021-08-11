#include <iostream>
#include "lib/bst.hpp"

auto main() -> int
{
  bst_<float> nums { 0, 3, 2, 5, 77, 33, -1, 88, 4, 1, -2, 0.5 };
  nums.print(3);
  std::puts("");
  std::cout << nums.max() << '\n';
  std::cout << nums.min() << '\n';
  std::cout << nums.find(22) << '\n';
  std::cout << nums.depth(5) << '\n';
  nums.remove(5);
  nums.print(2);
}
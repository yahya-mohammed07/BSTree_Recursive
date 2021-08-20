#include <iostream>
#include "lib/bst.hpp"

auto main() -> int
{
  bst_<float> nums { 0, 3, 2, 5, 77, 33, -1, 88, 4, 1, -2, 0.5 };
  nums.print(3);
  nums.remove(33);
  // nums.destroy_tree(); // FIXME: it's private because it causes leaks
  std::cout << '\n' << *nums.begin() << '\n';
  std::cout << nums.max() << '\n';
  std::cout << nums.min() << '\n';
  std::cout << nums.contains(5) << '\n';
  std::cout << nums.depth(5) << '\n';
  std::cout << *nums.get_parent(77) << '\n';

  if ( nums.find(5) != nums.end() ) {
    std::cout << *(++nums.find(5)) << '\n';
  }
  nums.remove(5);
  nums.print(2);
  std::puts("");
}
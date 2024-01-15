#include <algorithm>
#include <iostream>
#include <string>

void print_permutations(std::string str) {
  std::sort(std::begin(str), std::end(str));

  do {
    std::cout << str << std::endl;
  } while (std::next_permutation(std::begin(str), std::end(str)));
}

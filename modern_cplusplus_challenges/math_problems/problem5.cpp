#include <iostream>

bool is_prime(int const num) {
  if (num <= 3) {
    return num > 1;
  } else if (num % 2 == 0 || num % 3 == 0) {
    return false;
  } else {
    for (int i = 5; i * i <= num; i += 6) {
      if (num % i == 0 || num % (i + 2) == 0) {
        return false;
      }
    }
    return true;
  }
}

std::vector<std::pair<int, int>> get_max_prime(unsigned int limit) {
  std::vector<std::pair<int, int>> ret{};
  for (unsigned int i = 2; i < limit; i++) {
    if (is_prime(i) && is_prime(i + 6)) {
      ret.emplace_back(std::make_pair(i, i + 6));
    }
  }
  return ret;
}
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

unsigned int get_max_prime(unsigned int limit) {
  unsigned int ret{0};
  for (unsigned int i = limit; i > 0; i--) {
    if (is_prime(i)) {
      ret = i;
      break;
    }
  }
  return ret;
}
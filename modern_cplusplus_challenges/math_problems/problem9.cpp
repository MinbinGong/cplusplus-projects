#include <iostream>
#include <vector>

std::vector<unsigned long long> prime_factors(unsigned long long n) {
  std::vector<unsigned long long> factors{};
  while (n % 2 == 0) {
    factors.push_back(2);
    n = n / 2;
  }

  for (unsigned long long i = 3; i <= std::sqrt(n); i++) {
    while (n % i == 0) {
      factors.push_back(i);
      n = n / i;
    }
  }
  if (n > 2) {
    factors.push_back(n);
  }
  return factors;
}
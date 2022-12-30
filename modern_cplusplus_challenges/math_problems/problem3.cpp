#include <iostream>

unsigned int gcd(unsigned int a, unsigned int b) {
  while (b != 0) {
    unsigned int r = a % b;
    a = b;
    b = r;
  }

  return a;
}

int lcm(int const a, int const b)
{
  int h = gcd(a, b);
  return h ? (a * (b / h)) : 0;
}

template <class InputIt>
int lcmr(InputIt first, InputIt last) {
  return std::accumulate(first, last, 1, lcm);
}
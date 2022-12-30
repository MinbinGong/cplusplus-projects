#include <iostream>

#if 1
unsigned int gcd(unsigned int const a, unsigned int const b) {
  return b == 0 ? a : gcd(b, a % b);
}
#else
unsigned int gcd(unsigned int a, unsigned int b) {
  while (b != 0) {
    unsigned int r = a % b;
    a = b;
    b = r;
  }

  return a;
}
#endif

int main() {
  unsigned int a{0}, b{0};
  std::cout << "Input: a = ";
  std::cin >> a;
  std::cout << "Input: b = ";
  std::cin >> b;

  unsigned int gcd_value = gcd(a, b);
  std::cout << "gcd(" << a << ", " << b << ") = " << gcd_value << std::endl;

  return 0;
}

#include <iostream>

int main() {
  unsigned long x{0};
  std::cout << "Enter the maximum value: ";
  std::cin >> x;

  unsigned long long sum{0};
  for (unsigned int i = 0; i < x; i++) {
    if (i % 3 == 0 || i % 5 == 0) {
      sum += i;
    }
  }

  std::cout << "Sum = " << sum << std::endl;

  return 0;
}

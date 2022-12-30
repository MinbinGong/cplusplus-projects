#include <iostream>
#include <vector>

std::vector<int> get_narcissistics() {
  std::vector<int> ret{};
  for (int a = 1; a <= 9; a++) {
    for (int b = 0; b <= 9; b++) {
      for (int c = 0; c <= 9; c++) {
        auto abc = a * 100 + b * 10 + c;
        auto arm = a * a * a + b * b * b + c * c * c;
        if (abc == arm) {
          ret.push_back(arm);
        }
      }
    }
  }
  return ret;
}
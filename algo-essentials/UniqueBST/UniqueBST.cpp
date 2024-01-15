// UniqueBST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

int numTrees(int n) {
  std::vector<int> f(n + 1, 0);

  f[0] = 1;
  f[1] = 1;
  for (size_t i = 2; i <= n; i++) {
    for (size_t k = 1; k <= i; k++) {
      f[i] += f[k - 1] * f[i - k];
    }
  }

  return f[n];
}

int main() { std::cout << "Hello World!\n"; }

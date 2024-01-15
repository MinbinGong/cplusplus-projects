// FindMissingNumber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "pch.h"

int findMissingNumber(std::vector<int> &src, int N);

int main() {
  int N = 10;
  std::vector<int> src1{1, 2, 3, 4, 5, 6, 7, 8, 10};
  std::cout << findMissingNumber(src1, N) << std::endl;

  N = 5;
  std::vector<int> src2{1, 2, 3, 5};
  std::cout << findMissingNumber(src2, N) << std::endl;

  N = 5;
  std::vector<int> src3{1, 2, 3, 4, 5};
  std::cout << findMissingNumber(src3, N) << std::endl;

  return 0;
}

int findMissingNumber(std::vector<int> &src, int N) {
  int sum{0};
  for (unsigned int i = 0; i < src.size(); i++) {
    sum += src.at(i);
  }

  return (N * (N + 1) / 2 - sum);
}
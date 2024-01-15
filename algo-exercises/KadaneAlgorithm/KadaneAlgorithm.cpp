// KadaneAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <vector>

#include "pch.h"

std::vector<int> findSubarrayWithMaximumSum(std::vector<int> &src);

int main() {
  std::vector<int> srcV1{1, 2, 3, -1, 5};
  std::vector<int> subVec{};

  subVec = findSubarrayWithMaximumSum(srcV1);
  std::copy(subVec.begin(), subVec.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> srcV2{-1, -2, -3, -4};
  subVec = findSubarrayWithMaximumSum(srcV2);
  std::copy(subVec.begin(), subVec.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> srcV3{1, -2, -3, 4, 5, 6, -1, 12};
  subVec = findSubarrayWithMaximumSum(srcV3);
  std::copy(subVec.begin(), subVec.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  return 0;
}

std::vector<int> findSubarrayWithMaximumSum(std::vector<int> &src) {
  std::vector<int>::const_iterator itrB = src.cbegin(), itrE = src.cend();

  int prev{INT_MIN};
  for (auto i = src.cbegin(); i < src.cend(); i++) {
    int sum{*i};

    auto j = i + 1;
    for (; j < src.cend(); j++) {
      int value = sum + *j;
      if (sum > value && value < 0) {
        break;
      } else {
        sum = value;
      }
    }

    if (sum > prev) {
      itrB = i;
      itrE = j;
      prev = sum;
    }
  }

  return std::vector<int>(itrB, itrE);
}
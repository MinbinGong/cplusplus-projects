/*
 * @lc app=leetcode.cn id=583 lang=cpp
 * Power of Three
 * 判断一个数字是否是 3 的次方。
 */
#include <cmath>

using namespace std;

class Solution {
 public:
  bool isPowerOfThree(int n) {
    if (n <= 0) return false;
    double x = log10(n) / log10(3);
    return abs(x - round(x)) < 1e-10;
  }
};
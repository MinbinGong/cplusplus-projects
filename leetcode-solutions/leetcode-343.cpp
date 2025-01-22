/*
 * @lc app=leetcode.cn id=343 lang=cpp
 * Given an integer n, break it into the sum of k positive integers, where k >= 2,
 * and maximize the product of those integers.
 * 
 * Return the maximum product you can get.
 */
#include <algorithm>
#include <vector>
using namespace std;

int integerBreak(int n) {
  vector<int> dp(n + 1, 1);
  for (int j = 2; j <= n; j++) {
    for (int i = 1; i < j; i++) {
      dp[j] = max(dp[j], i * (j - i));
      dp[j] = max(dp[j], i * dp[j - i]);
    }
  }
  return dp[n];
}
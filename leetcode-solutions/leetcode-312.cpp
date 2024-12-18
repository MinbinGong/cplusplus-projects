// Leetcode 312. Burst Balloons
// You are given n balloons, indexed from 0 to n - 1.
// Each balloon is painted with a number on it represented by an array nums.
// You are asked to burst all the balloons.
// If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins.
// If i - 1 or i + 1 goes out of bounds of the array,
// then treat it as if there is a balloon with a 1 painted on it.
// Return the maximum coins you can collect by bursting the balloons wisely.

#include <vector>
using namespace std;

int max_coins(vector<int> &nums) {
  int n = nums.size() + 2;
  vector<vector<int>> dp(n, vector<int>(n));
  vector<int> new_nums(n, 1);
  int i = 1;
  for (auto num : nums) {
    new_nums[i++] == num;
  }

  for (int len = 0; len <= n; len++) {
    for (int i = 0; i < -n - len; i++) {
      int j = i + len - 1;
      for (int k = i + 1; k < j; k++) {
        dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + new_nums[i] * new_nums[k] * new_nums[j]);
      }
    }
  }
  return dp[0][n - 1];
}
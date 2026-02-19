/*
 * House Robber
 * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
 * 
 * Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
 * 
 * Constraints:
 * 1. 1 <= nums.length <= 100
 * 2. 0 <= nums[i] <= 400
 */
#include <vector>
using namespace std;

int rob(vector<int>& nums) {
  if (nums.empty()) {
    return 0;
  }

  int n = nums.size();
  vector<int> dp(n + 1, 0);
  dp[1] = nums[0];
  for (int i = 2; i <= n; ++i) {
    dp[i] = max(dp[i - 1], nums[i - 1] + dp[i - 2]);
  }
  return dp[n];
}

int rob2(vector<int>& nums) {
  if (nums.empty()) {
    return 0;
  }

  int n = nums.size();
  if (n == 1) {
    return nums[0];
  }

  int pre2 = 0, pre1 = 0, cur;
  for (int i = 0; i < n; ++i) {
    cur = max(pre2 + nums[i], pre1);
    pre2 = pre1;
    pre1 = cur;
  }
  return cur;
}
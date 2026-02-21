/*
 * leetcode-368: Largest Divisible Subset
 *
 * Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:
 * 
 * answer[i] % answer[j] == 0, or
 * answer[j] % answer[i] == 0
 * If there are multiple solutions, return any of them.
 * 
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: [1,2]
 * Explanation: [1,3] is also accepted.
 * 
 * Example 2:
 * Input: nums = [1,2,4,8]
 * Output: [1,2,4,8]
 * 
 * Constraints:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 2 * 109
 * All the integers in nums are unique.
 * 
 */
#include <algorithm>
#include <vector>
using namespace std;

vector<int> largestDivisibleSubset(vector<int>& nums) {
  if (nums.size() == 0 || nums.size() == 1) return nums;

  sort(nums.begin(), nums.end());
  vector<int> dp(nums.size(), 1);
  for (int i = 1; i < nums.size(); i++) {
    for (int j = 0; j < i; j++) {
      if (nums[i] % nums[j] == 0) {
        dp[i] = max(dp[i], 1 + dp[j]);
      }
    }
  }

  int maxi = *max_element(dp.begin(), dp.end());

  int prev = -1;
  int i = dp.size() - 1;
  vector<int> res;
  while (i >= 0) {
    if (dp[i] == maxi && (prev % nums[i] == 0 || prev == -1)) {
      res.push_back(nums[i]);
      maxi--;
      prev = nums[i];
    }
    i--;
  }
  return res;
}
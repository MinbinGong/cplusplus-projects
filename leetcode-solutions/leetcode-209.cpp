/*
 * Minimum Size Subarray Sum
 * Given an array of positive integers nums and a positive integer target, return the minimal length of a
 * subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.
 *
 * Constraints:
 * 1. 1 <= target <= 10^9
 * 2. 1 <= nums.length <= 10^5
 * 3. 1 <= nums[i] <= 10^4
 */
#include <climits>
#include <vector>
using namespace std;

int minSubArrayLen(int target, vector<int>& nums) {
  int left = 0;
  int sum = 0;
  int minLen = INT_MAX;

  for (int right = 0; right < nums.size(); ++right) {
    sum += nums[right];

    // Shrink the window as much as possible while sum >= target
    while (sum >= target) {
      minLen = min(minLen, right - left + 1);
      sum -= nums[left];
      left++;
    }
  }

  return (minLen == INT_MAX) ? 0 : minLen;
}

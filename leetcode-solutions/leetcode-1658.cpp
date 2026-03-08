/**
 * 1658. Minimum Operations to Reduce X to Zero
 * 
 * You are given an integer array nums and an integer x. In one operation, you can either remove the leftmost or the rightmost element from the array nums and subtract its value from x. Note that this modifies the array for future operations.
 * 
 * Return the minimum number of operations to reduce x to exactly 0 if it is possible, otherwise, return -1.
 * 
 * Example 1:
 * Input: nums = [1,1,4,2,3], x = 5
 * Output: 2
 * Explanation: The optimal solution is to remove the last two elements to reduce x to zero.
 * 
 * Example 2:
 * Input: nums = [5,6,7,8,9], x = 4
 * Output: -1
 * Explanation: It is impossible to reduce x to zero.
 * 
 * Example 3:
 * Input: nums = [3,2,20,1,1,3], x = 10
 * Output: 5
 * Explanation: The optimal solution is to remove the last three elements and the first two elements (5 operations in total) to reduce x to zero.
 * 
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^4
 * 1 <= x <= 10^9
 * 
 */
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        int target = total - x;
        if (target < 0) return -1;          // 总和小于 x，不可能
        if (target == 0) return nums.size(); // 需要移除所有元素

        int left = 0, sum = 0, maxLen = -1;
        for (int right = 0; right < nums.size(); ++right) {
            sum += nums[right];
            // 收缩窗口直到 sum <= target
            while (sum > target && left <= right) {
                sum -= nums[left++];
            }
            if (sum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }
        return maxLen == -1 ? -1 : nums.size() - maxLen;
    }
};
/*
 * 1608. Special Array With X Elements Greater Than or Equal X
 *
 * You are given an array nums of non-negative integers. nums is considered special if there exists a number x such that there are exactly x numbers in nums that are greater than or equal to x.
 *
 * Notice that x does not have to be an element in nums.
 *
 * Return x if the array is special, otherwise, return -1. It can be proven that if nums is special, the value for x is unique.
 *
 * Example 1:
 * Input: nums = [3,5]
 * Output: 2
 * Explanation: There are 2 values (3 and 5) that are greater than or equal to 2.
 * 
 * Example 2:
 * Input: nums = [0,0]
 * Output: -1
 * Explanation: There is no x that satisfies the condition.
 * 
 * Example 3:
 * Input: nums = [0,4,3,0,4]
 * Output: 3
 * Explanation: There are 3 values that are greater than or equal to 3.
 * 
 * Example 4:
 * Input: nums = [3,6,7,7,0]
 * Output: -1
 * 
 * Constraints:
 * 1 <= nums.length <= 100
 * 0 <= nums[i] <= 1000
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int specialArray(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int x = 0; x <= n; ++x) {
            // 找到第一个 >= x 的元素位置
            int idx = lower_bound(nums.begin(), nums.end(), x) - nums.begin();
            int count = n - idx; // 大于等于 x 的元素个数
            if (count == x) return x;
        }
        return -1;
    }
};
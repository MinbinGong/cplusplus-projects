/*
 * Non-decreasing Array
 *
 * Given an array with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.
 *
 * We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).
 *
 * Example 1:
 *
 * Input: [4,2,3]
 * Output: True
 * Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
 *
 * Example 2:
 *
 * Input: [4,2,1]
 * Output: False
 * Explanation: You can't get a non-decreasing array by modify at most one element.
 *
 * Note: The n belongs to [1, 10,000].
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0, idx = -1;
        for (int i = 0; i < n - 1; ++i) {
            if (nums[i] > nums[i + 1]) {
                if (++cnt > 1) return false;
                idx = i;
            }
        }
        if (cnt == 0) return true;
        // Only one decreasing pair at index idx
        if (idx == 0 || idx == n - 2) return true;
        // Check if we can fix by either lowering left or raising right
        if (nums[idx - 1] <= nums[idx + 1]) return true;
        if (nums[idx] <= nums[idx + 2]) return true;
        return false;
    }
};
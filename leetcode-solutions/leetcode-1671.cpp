/*
 * 1671. Minimum Number of Removals to Make Mountain Array
 * 
 * You may recall that an array arr is a mountain array if and only if:
 * 
 * arr.length >= 3
 * There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
 * arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
 * arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 * Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain array.
 * 
 * Example 1:
 * Input: nums = [1,3,1]
 * Output: 0
 * Explanation: The array itself is a mountain array so we do not need to remove any elements.
 * 
 * Example 2:
 * Input: nums = [2,1,1,5,6,2,3,1]
 * Output: 3
 * Explanation: One solution is to remove the elements at indices 0, 1, and 5, making the array nums = [1,5,6,3,1].
 * 
 * Constraints:
 * 3 <= nums.length <= 1000
 * 1 <= nums[i] <= 10^9
 * It is guaranteed that you can make a mountain array out of nums.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n, 1);  // left[i] 表示以 i 结尾的最长严格递增子序列长度
        vector<int> right(n, 1); // right[i] 表示以 i 开头的最长严格递减子序列长度

        // 计算 left 数组
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    left[i] = max(left[i], left[j] + 1);
                }
            }
        }

        // 计算 right 数组（从右往左看，相当于以 i 开头的最长递减子序列）
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                if (nums[j] < nums[i]) {
                    right[i] = max(right[i], right[j] + 1);
                }
            }
        }

        // 寻找可能的最长山脉子数组长度
        int maxMountain = 0;
        for (int i = 0; i < n; ++i) {
            if (left[i] >= 2 && right[i] >= 2) { // 递增和递减部分至少各有两个元素
                maxMountain = max(maxMountain, left[i] + right[i] - 1);
            }
        }

        return n - maxMountain; // 最少删除次数
    }
};
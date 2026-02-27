/**
 * 1144. Decrease Elements To Make Array Zigzag
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * Given an array nums of integers, a move consists of choosing any element and decreasing it by 1.
 * 
 * An array A is a zigzag array if either:
 * 
 * Every even-indexed element is greater than adjacent elements, ie. A[0] > A[1] < A[2] > A[3] < A[4] > ...
 * OR, every odd-indexed element is greater than adjacent elements, ie. A[0] < A[1] > A[2] < A[3] > A[4] < ...
 * Return the minimum number of moves to transform the given array nums into a zigzag array.
 * 
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: 2
 * Explanation: We can decrease 2 to 0 or 3 to 1.
 * 
 * Example 2:
 * Input: nums = [9,6,1,6,2]
 * Output: 4
 * Explanation: We can decrease 9 to 8, 6 to 5, 6 to 5, and 2 to 1.
 * 
 * Note:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 1000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int movesToMakeZigzag(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        
        int ans0 = 0; // 模式0：偶数索引为峰，奇数索引为谷
        for (int i = 1; i < n; i += 2) { // 遍历所有奇数索引（谷）
            int left = (i - 1 >= 0) ? nums[i - 1] : INT_MAX;   // 左邻峰
            int right = (i + 1 < n) ? nums[i + 1] : INT_MAX;   // 右邻峰
            int target = min(left, right) - 1;                 // 谷需要 ≤ target
            if (nums[i] > target) {
                ans0 += nums[i] - target;                      // 需要减少的量
            }
        }
        
        int ans1 = 0; // 模式1：奇数索引为峰，偶数索引为谷
        for (int i = 0; i < n; i += 2) { // 遍历所有偶数索引（谷）
            int left = (i - 1 >= 0) ? nums[i - 1] : INT_MAX;
            int right = (i + 1 < n) ? nums[i + 1] : INT_MAX;
            int target = min(left, right) - 1;
            if (nums[i] > target) {
                ans1 += nums[i] - target;
            }
        }
        
        return min(ans0, ans1);
    }
};
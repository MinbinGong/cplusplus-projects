/**
 * 1746. Maximum Subarray Sum After One Operation
 * 
 * You are given an integer array nums. You must perform exactly one operation
 * where you can replace one element nums[i] with nums[i] * nums[i].
 * 
 * Return the maximum possible subarray sum after exactly one operation. The
 * subarray must be non-empty.
 * 
 * Example 1:
 * 
 * Input: nums = [2,-1,-4,-3]
 * Output: 17
 * Explanation: You can perform the operation on index 2 (0-indexed) to make
 * nums = [2,-1,16,-3]. Now, the maximum subarray sum is 2 + -1 + 16 = 17.
 * 
 * Example 2:
 * 
 * Input: nums = [1,-1,1,1,-1,-1,1]
 * Output: 4
 * Explanation: You can perform the operation on index 1 (0-indexed) to make
 * nums = [1,-1,1,1,-1,-1,1]. Now, the maximum subarray sum is 1 + -1 + 1 + 1 = 4.
 * 
 * Constraints:
 * 
 * 1 <= nums.length <= 105
 * -104 <= nums[i] <= 104
 * 
 */
#include <vector>
using namespace std;

class Solution1 {
public:
    int maxSumAfterOperation(vector<int>& nums) {
        int f = 0;      // 未使用操作的最大子数组和
        int g = 0;      // 已使用操作的最大子数组和
        int ans = INT_MIN;
        
        for (int x : nums) {
            int new_f = max(f, 0) + x;
            int new_g = max(max(f, 0) + x * x, g + x);
            
            f = new_f;
            g = new_g;
            
            ans = max({ans, f, g});
        }
        
        return ans;
    }
};

class Solution2 {
public:
    int maxSumAfterOperation(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2));
        
        // 初始化
        dp[0][0] = nums[0];              // 未使用操作
        dp[0][1] = nums[0] * nums[0];    // 使用操作
        
        int ans = dp[0][1];  // 至少有一个操作
        
        for (int i = 1; i < n; i++) {
            // 未使用操作：要么重新开始，要么接上之前的
            dp[i][0] = max(nums[i], dp[i-1][0] + nums[i]);
            
            // 已使用操作：两种情况取最大
            // 1. 在当前位置使用操作：之前未使用 + 当前平方
            // 2. 之前已使用操作：当前直接加上
            dp[i][1] = max(dp[i-1][0] + nums[i] * nums[i], 
                          dp[i-1][1] + nums[i]);
            
            ans = max(ans, dp[i][1]);
        }
        
        return ans;
    }
};
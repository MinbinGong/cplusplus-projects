/*
 * @lc app=leetcode.cn id=494 lang=cpp
 * Target Sum
 * You are given an integer array nums and an integer target.
 * 
 * You want to build an expression out of nums by adding one of the symbols '+' and '-'
 * before each integer in nums and then concatenate all the integers.
 * 
 * For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1
 * and concatenate them to build the expression "+2-1".
 * Return the number of different expressions that you can build, which evaluates to target.
 */

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// class Solution {
// public:
//     int findTargetSumWays(vector<int>& nums, int target) {
//         int sum = 0;
//         for (int num : nums) {
//             sum += num;
//         }
//         int diff = sum - target;
//         if (diff < 0 || diff % 2 != 0) {
//             return 0;
//         }
//         int n = nums.size(), neg = diff / 2;
//         vector<vector<int>> dp(n + 1, vector<int>(neg + 1));
//         dp[0][0] = 1;
//         for (int i = 1; i <= n; i++) {
//             int num = nums[i - 1];
//             for (int j = 0; j <= neg; j++) {
//                 dp[i][j] = dp[i - 1][j];
//                 if (j >= num) {
//                     dp[i][j] += dp[i - 1][j - num];
//                 }
//             }
//         }
//         return dp[n][neg];
//     }
// };

int findTargetSumWays(vector<int>& nums, int target) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    int diff = sum - target;
    if (diff < 0 || diff % 2!= 0) {
        return 0;
    }
    int n = nums.size(), neg = diff / 2;
    vector<int> dp(neg + 1);
    dp[0] = 1;
    for (int num : nums) {
        for (int j = neg; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }
    return dp[neg];
}
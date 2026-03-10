/*
 * 1714. Minimum Operations to Make a Subsequence
 * 
 * You are given an array target that consists of distinct integers and another integer array arr that can have duplicates.
 * 
 * In one operation, you can insert any integer at any position in arr. For example, if arr = [1,4,1,2], you can add 3 in the middle and make it [1,4,3,1,2]. Note that you can insert the integer at the very beginning or end of the array.
 * 
 * Return the minimum number of operations needed to make target a subsequence of arr.
 * 
 * A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.
 * 
 * Example 1:
 * Input: target = [5,1,3], arr = [9,4,2,3,4]
 * Output: 2
 * Explanation: You can add 5 and 1 in such a way that makes arr = [5,9,4,1,2,3,4], then target will be a subsequence of arr.
 * 
 * Example 2:
 * Input: target = [6,4,8,1,3,2], arr = [4,7,6,2,3,8,6,1]
 * Output: 3
 * 
 * Constraints:
 * 1 <= target.length, arr.length <= 10^5
 * 1 <= target[i], arr[i] <= 10^9
 * target contains no duplicates.
 * 
 */
#include <vector>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> solve(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        // 将步长阈值设为 sqrt(n)，进行分块
        int m = (int) sqrt(n);
        const int MOD = 1e9 + 7;
        
        // 预处理：suf[y][x] 表示从下标 x 开始，步长为 y 的所有元素之和
        // 只预处理步长 <= m 的情况
        int suf[m + 1][n + 1];
        memset(suf, 0, sizeof(suf));
        
        // 从后往前预处理后缀和
        for (int step = 1; step <= m; ++step) {
            for (int i = n - 1; i >= 0; --i) {
                int next = i + step;
                if (next < n) {
                    suf[step][i] = (suf[step][next] + nums[i]) % MOD;
                } else {
                    suf[step][i] = nums[i] % MOD;
                }
            }
        }
        
        vector<int> ans;
        for (auto& q : queries) {
            int x = q[0], y = q[1];
            if (y <= m) {
                // 小步长：直接使用预处理结果
                ans.push_back(suf[y][x] % MOD);
            } else {
                // 大步长：直接循环累加（步长大，循环次数少）
                long long sum = 0;
                for (int i = x; i < n; i += y) {
                    sum = (sum + nums[i]) % MOD;
                }
                ans.push_back(sum % MOD);
            }
        }
        return ans;
    }
};
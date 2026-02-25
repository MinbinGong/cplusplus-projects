/*
 * 956. Tallest Billboard
 *
 * You are installing a billboard and want it to have the largest height. The billboard will have two steel supports, one on each side. Each steel support must be an equal height.
 *
 * You are given a collection of rods that can be welded together. For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.
 *
 * Return the largest possible height of your billboard installation. If you cannot support the billboard, return 0.
 *
 * Example 1:
 *
 * Input: rods = [1,2,3,6]
 * Output: 6
 * Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
 *
 * Example 2:
 *
 * Input: rods = [1,2,3,4,5,6]
 * Output: 10
 * Explanation: We have two disjoint subsets {1,2,4} and {3,5,6}, which have the same sum = 10.
 *
 * Example 3:
 *
 * Input: rods = [1,2]
 * Output: 0
 * Explanation: The billboard cannot be supported, so we return 0.
 *
 * Note:
 *
 * 1 <= rods.length <= 20
 * 1 <= rods[i] <= 1000
 * sum(rods[i]) <= 5000
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution1 {
public:
    int tallestBillboard(vector<int>& rods) {
        // dp[d] = 当高度差为 d 时，较低支架的最大高度
        // 使用 unordered_map 存储，初始状态差为0，高度为0
        unordered_map<int, int> dp;
        dp[0] = 0;
        
        for (int rod : rods) {
            // 必须基于上一轮的状态进行更新，所以先拷贝一份
            unordered_map<int, int> cur(dp);
            
            for (auto& [diff, height] : cur) {
                // 1. 将 rod 放到较高支架：高度差增大
                dp[diff + rod] = max(dp[diff + rod], height);
                
                // 2. 将 rod 放到较低支架
                // 新的高度差为 abs(diff - rod)
                // 新的较低支架高度 = height + min(diff, rod)
                int newDiff = abs(diff - rod);
                int newHeight = height + min(diff, rod);
                dp[newDiff] = max(dp[newDiff], newHeight);
            }
        }
        
        // 差值为0时的最大共同高度即为答案
        return dp[0];
    }
};

class Solution2 {
public:
    int tallestBillboard(vector<int>& rods) {
        int sum = accumulate(rods.begin(), rods.end(), 0);
        // dp[diff] = 较低支架的最大高度，初始化为 -1 表示不可达
        vector<int> dp(sum + 1, -1);
        dp[0] = 0;
        
        for (int rod : rods) {
            vector<int> cur(dp); // 拷贝当前状态
            for (int diff = 0; diff <= sum - rod; ++diff) {
                if (cur[diff] < 0) continue; // 当前差值不可达
                
                // 放到较高支架
                dp[diff + rod] = max(dp[diff + rod], cur[diff]);
                
                // 放到较低支架
                int newDiff = abs(diff - rod);
                int newHeight = cur[diff] + min(diff, rod);
                dp[newDiff] = max(dp[newDiff], newHeight);
            }
        }
        
        return dp[0];
    }
};
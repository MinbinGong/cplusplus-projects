/*
 * 813. Largest Sum of Averages
 * 
 * We partition a row of numbers nums into at most k adjacent (non-empty) groups, then our score is the sum of the average of each group. What is the largest score we can achieve?
 * 
 * Note that our partition must use every number in nums, and that scores are not necessarily integers.
 * 
 * Example:
 * Input: 
 * nums = [9,1,2,3,9]
 * k = 3
 * Output: 20.00000
 * Explanation: 
 * The best choice is to partition nums into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
 * We could have also partitioned nums into [9, 1], [2], [3, 9], for example.
 * That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
 * 
 * Note:
 * 1 <= nums.length <= 100.
 * 1 <= nums[i] <= 10000.
 * 1 <= k <= nums.length.
 * Answers within 10-6 of the actual answer will be accepted as correct.
 * 
 */
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int K) {
        int n = nums.size();
        // 前缀和，方便计算子数组和
        vector<double> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // dp[k][i] 表示将前 i 个元素分成 k 组所能得到的最大平均值和
        // 初始化为负无穷，因为可能取到负数
        vector<vector<double>> dp(K + 1, vector<double>(n + 1, -1e18));
        dp[0][0] = 0;  // 0 个元素分成 0 组，和为 0

        for (int k = 1; k <= K; ++k) {
            for (int i = k; i <= n; ++i) {          // 至少需要 k 个元素
                for (int j = k - 1; j < i; ++j) {   // 前 j 个分成 k-1 组，最后一段 [j+1, i]
                    double avg = (prefix[i] - prefix[j]) / (i - j);
                    dp[k][i] = max(dp[k][i], dp[k - 1][j] + avg);
                }
            }
        }

        return dp[K][n];
    }
};
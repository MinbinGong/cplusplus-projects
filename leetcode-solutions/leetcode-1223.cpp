/**
 * 1223. Dice Roll Simulation
 *
 * A die simulator generates a random number from 1 to 6 for each roll. You introduced a constraint to the generator such that it cannot roll the number i more than rollMax[i] (1-indexed) consecutive times.
 *
 * Given an array of integers rollMax and an integer n, return the number of distinct sequences that can be obtained with exact n rolls.
 *
 * Two sequences are considered different if at least one element differs from each other. Since the answer may be too large, return it modulo 10^9 + 7.
 *
 *
 *
 * Example 1:
 *
 * Input: n = 2, rollMax = [1,1,2,2,2,3]
 * Output: 34
 * Explanation: Total possible sequences are "aa", "ae", "ea", "ee", "ia", "ie", "io", "iu", "oi", "ou", "ua", "ue", "ui", "uo", "uu".
 * Total of 34 sequences are possible.
 *
 * Example 2:
 *
 * Input: n = 2, rollMax = [1,1,1,1,1,1]
 * Output: 30
 *
 * Example 3:
 *
 * Input: n = 3, rollMax = [1,1,1,2,2,3]
 * Output: 181
 *
 *
 * Constraints:
 *
 * 1 <= n <= 5000
 * rollMax.length == 6
 * 1 <= rollMax[i] <= 15
 *
 */
#include <vector>
#include <cstring>

using namespace std;

class Solution1 {
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        const int MOD = 1e9 + 7;
        const int MAX_ROLL = 15; // 根据题目，rollMax[i] 的最大值为 15
        
        // dp[i][j][k] 表示投掷i次，最后一次投掷数字为j+1，且这个数字连续出现了k次的序列数
        vector<vector<vector<long long>>> dp(
            n + 1, vector<vector<long long>>(6, vector<long long>(MAX_ROLL + 1, 0)));
        
        // 初始化：第一次投掷
        for (int j = 0; j < 6; ++j) {
            dp[1][j][1] = 1;
        }
        
        // 动态规划
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < 6; ++j) {
                for (int k = 1; k <= MAX_ROLL; ++k) {
                    if (dp[i-1][j][k] == 0) continue;
                    
                    // 投掷不同的数字
                    for (int p = 0; p < 6; ++p) {
                        if (p != j) {
                            dp[i][p][1] = (dp[i][p][1] + dp[i-1][j][k]) % MOD;
                        }
                    }
                    
                    // 投掷相同的数字，检查是否超过最大连续次数
                    if (k + 1 <= rollMax[j]) {
                        dp[i][j][k+1] = (dp[i][j][k+1] + dp[i-1][j][k]) % MOD;
                    }
                }
            }
        }
        
        // 计算结果
        long long result = 0;
        for (int j = 0; j < 6; ++j) {
            for (int k = 1; k <= MAX_ROLL; ++k) {
                result = (result + dp[n][j][k]) % MOD;
            }
        }
        
        return result;
    }
};

// 优化版：使用滚动数组减少空间复杂度
class Solution2 {
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        const int MOD = 1e9 + 7;
        const int MAX_ROLL = 15;
        
        // dp[j][k] 表示当前步以数字j+1结尾，且连续出现k次的序列数
        vector<vector<long long>> dp(6, vector<long long>(MAX_ROLL + 1, 0));
        vector<vector<long long>> prev(6, vector<long long>(MAX_ROLL + 1, 0));
        
        // 初始化第一次投掷
        for (int j = 0; j < 6; ++j) {
            dp[j][1] = 1;
        }
        
        for (int i = 2; i <= n; ++i) {
            // 交换dp和prev
            prev = dp;
            dp = vector<vector<long long>>(6, vector<long long>(MAX_ROLL + 1, 0));
            
            for (int j = 0; j < 6; ++j) {
                for (int k = 1; k <= MAX_ROLL; ++k) {
                    if (prev[j][k] == 0) continue;
                    
                    // 投掷不同的数字
                    for (int p = 0; p < 6; ++p) {
                        if (p != j) {
                            dp[p][1] = (dp[p][1] + prev[j][k]) % MOD;
                        }
                    }
                    
                    // 投掷相同的数字
                    if (k + 1 <= rollMax[j]) {
                        dp[j][k+1] = (dp[j][k+1] + prev[j][k]) % MOD;
                    }
                }
            }
        }
        
        // 计算结果
        long long result = 0;
        for (int j = 0; j < 6; ++j) {
            for (int k = 1; k <= MAX_ROLL; ++k) {
                result = (result + dp[j][k]) % MOD;
            }
        }
        
        return result;
    }
};

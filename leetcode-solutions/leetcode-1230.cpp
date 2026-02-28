/*
 * 1230. Toss Strange Coins
 *
 * You have some coins.  The i-th coin has a probability prob[i] of facing heads when tossed.
 *
 * Return the probability that the number of coins facing heads equals target if you toss every coin exactly once.
 *
 * Example 1:
 * 
 * Input: prob = [0.4], target = 1
 * Output: 0.40000
 * Explanation: 1 out of 2 possibilities is that a single coin toss results in a head.
 * 
 * Example 2:
 * 
 * Input: prob = [0.5,0.5,0.5,0.5,0.5], target = 0
 * Output: 0.03125
 * Explanation: 5 of the 10 possibilities are that no coin toss results in a head.
 * 
 * Note:
 * 1 <= prob.length <= 1000
 * 0 <= prob[i] <= 1
 * 0 <= target <= prob.length
 * Answers will be accepted as correct if they are within 10^-5 of the correct answer.
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution1 {
public:
    double probabilityOfHeads(vector<double>& prob, int target) {
        int n = prob.size();
        
        // dp[i][j]: 前i个硬币中有j个正面的概率
        vector<vector<double>> dp(n + 1, vector<double>(target + 1, 0.0));
        
        // 初始化：0个硬币0个正面的概率为1
        dp[0][0] = 1.0;
        
        for (int i = 1; i <= n; ++i) {
            // 当前硬币的概率
            double p = prob[i - 1];
            
            // j=0的情况：所有硬币都是反面
            dp[i][0] = dp[i - 1][0] * (1 - p);
            
            // 计算其他j值
            for (int j = 1; j <= min(i, target); ++j) {
                // 状态转移方程：
                // 1. 前i-1个硬币有j-1个正面，当前硬币正面：dp[i-1][j-1] * p
                // 2. 前i-1个硬币有j个正面，当前硬币反面：dp[i-1][j] * (1-p)
                dp[i][j] = dp[i - 1][j - 1] * p + dp[i - 1][j] * (1 - p);
            }
        }
        
        return dp[n][target];
    }
};

// 方法2：空间优化版本（一维数组）
class Solution2 {
public:
    double probabilityOfHeads(vector<double>& prob, int target) {
        int n = prob.size();
        
        // dp[j]: 当前处理到第i个硬币时，有j个正面的概率
        vector<double> dp(target + 1, 0.0);
        dp[0] = 1.0;  // 0个正面的初始概率
        
        for (int i = 0; i < n; ++i) {
            double p = prob[i];
            
            // 需要从后往前更新，避免使用被覆盖的旧值
            for (int j = min(i + 1, target); j >= 1; --j) {
                dp[j] = dp[j - 1] * p + dp[j] * (1 - p);
            }
            
            // 更新j=0的情况
            dp[0] = dp[0] * (1 - p);
        }
        
        return dp[target];
    }
};

// 方法3：递归+记忆化搜索
class Solution3 {
public:
    double probabilityOfHeads(vector<double>& prob, int target) {
        int n = prob.size();
        vector<vector<double>> memo(n, vector<double>(target + 1, -1.0));
        return dfs(prob, 0, target, memo);
    }
    
private:
    double dfs(vector<double>& prob, int idx, int k, vector<vector<double>>& memo) {
        if (k < 0) return 0.0;
        if (idx == prob.size()) {
            return k == 0 ? 1.0 : 0.0;
        }
        
        if (memo[idx][k] != -1.0) {
            return memo[idx][k];
        }
        
        double p = prob[idx];
        // 当前硬币正面
        double heads = dfs(prob, idx + 1, k - 1, memo) * p;
        // 当前硬币反面
        double tails = dfs(prob, idx + 1, k, memo) * (1 - p);
        
        memo[idx][k] = heads + tails;
        return memo[idx][k];
    }
};

// 测试用例示例：
// 输入: prob = [0.5,0.5,0.5], target = 0
// 输出: 0.125
// 解释: 所有硬币都是反面的概率 = 0.5 * 0.5 * 0.5 = 0.125
//
// 输入: prob = [0.5,0.5,0.5], target = 1
// 输出: 0.375
// 解释: 恰好一个正面的概率 = C(3,1) * 0.5^1 * 0.5^2 = 3 * 0.125 = 0.375
//
// 输入: prob = [0.4], target = 1
// 输出: 0.4
// 解释: 只有一个硬币，正面的概率就是0.4
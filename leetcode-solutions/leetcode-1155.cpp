/**
 * 1155. Number of Dice Rolls With Target Sum
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * You have d dice, and each die has f faces numbered 1, 2, ..., f.
 * 
 * Return the number of possible ways (out of fd total ways) modulo 10^9 + 7 to roll the dice so the sum of the face up numbers equals target.
 * 
 * Example 1:
 * Input: d = 1, f = 6, target = 3
 * Output: 1
 * Explanation: 
 * You throw one die with 6 faces.  There is only one way to get a sum of 3.
 * 
 * Example 2:
 * Input: d = 2, f = 6, target = 7
 * Output: 6
 * Explanation: 
 * You throw two dice, each with 6 faces.  There are 6 ways to get a sum of 7:  
 * 1+6, 2+5, 3+4, 4+3, 5+2, 6+1.
 * 
 * Example 3:
 * Input: d = 2, f = 5, target = 10
 * Output: 1
 * Explanation: 
 * You throw two dice, each with 5 faces.  There is only one way to get a sum of 10: 5+5.
 * 
 * Example 4:
 * Input: d = 1, f = 2, target = 3
 * Output: 0
 * Explanation: 
 * You throw one die with 2 faces.  There is no way to get a sum of 3.
 * 
 * Note:
 * 1 <= d, f <= 30
 * 1 <= target <= 1000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        const int MOD = 1e9 + 7;
        vector<int> dp(target + 1, 0);
        dp[0] = 1; // 0个骰子，总和为0的方法数为1

        for (int i = 1; i <= n; ++i) {
            vector<int> new_dp(target + 1, 0);
            for (int sum = 1; sum <= target; ++sum) {
                // 枚举当前骰子的点数
                for (int face = 1; face <= k; ++face) {
                    if (sum - face >= 0) {
                        new_dp[sum] = (new_dp[sum] + dp[sum - face]) % MOD;
                    }
                }
            }
            dp = move(new_dp);
        }
        return dp[target];
    }
};
/**
 * 879. Profitable Schemes
 *
 * There is a group of n members, and a list of various crimes they could commit.
 * The ith crime generates a profit[i] and requires group[i] members to participate in it.
 * If a member participates in one crime, that member can't participate in another crime.
 *
 * Let's call a profitable scheme any subset of these crimes that generates at least minProfit profit,
 * and the total number of members participating in that subset of crimes is at most n.
 *
 * Return the number of schemes that can be chosen. Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * Example 1:
 * Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
 * Output: 2
 * Explanation: To make a profit of at least 3, the group could either commit crimes 0 and 1, or just crime 1.
 * In total, there are 2 schemes.
 *
 * Example 2:
 * Input: n = 10, minProfit = 5, group = [2,3,5], profit = [6,7,8]
 * Output: 7
 * Explanation: To make a profit of at least 5, the group could commit any crimes, as long as they commit one.
 * There are 7 possible schemes: (0), (1), (2), (0,1), (0,2), (1,2), and (0,1,2).
 *
 * Note:
 * 1 <= n <= 100
 * 0 <= minProfit <= 100
 * 1 <= group.length <= 100
 * 1 <= group[i] <= 100
 * profit.length == group.length
 * 0 <= profit[i] <= 100
 * 
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        const int MOD = 1e9 + 7;
        int m = group.size();
        // dp[p][k] 表示利润至少为 p 且使用恰好 k 人的方案数
        // 由于利润超过 minProfit 的可以压缩到 minProfit，所以第一维大小为 minProfit+1
        vector<vector<int>> dp(minProfit + 1, vector<int>(n + 1, 0));
        dp[0][0] = 1;  // 初始状态：利润0，0人，1种方案（什么都不做）

        for (int i = 0; i < m; ++i) {
            int g = group[i];   // 需要的人数
            int p = profit[i];  // 获得的利润
            // 逆序更新，保证每个犯罪只用一次（0/1背包）
            for (int j = minProfit; j >= 0; --j) {
                for (int k = n - g; k >= 0; --k) {
                    int newProfit = min(minProfit, j + p);
                    dp[newProfit][k + g] = (dp[newProfit][k + g] + dp[j][k]) % MOD;
                }
            }
        }

        // 累加所有人数下利润达到 minProfit 的方案数
        int ans = 0;
        for (int k = 0; k <= n; ++k) {
            ans = (ans + dp[minProfit][k]) % MOD;
        }
        return ans;
    }
};
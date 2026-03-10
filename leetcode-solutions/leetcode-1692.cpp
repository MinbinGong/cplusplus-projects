/*
 * 1692. Count Ways to Distribute Candies
 * 
 * You have n candies, the ith candy is of type candies[i].
 * You want to distribute the candies equally between a sister and a brother. You can give any number of candies to each child.
 * 
 * Return the maximum number of different types of candies the sister could gain.
 * 
 * Example 1:
 * Input: candies = [1,2,2,3,3,3]
 * Output: 3
 * Explanation:
 * There are three different kinds of candies (1, 2 and 3), and two candies for each kind.
 * Optimal distribution: The sister has candies [1,2,3] and the brother has candies [2,3,3].
 * The sister has three different kinds of candies.
 * 
 * Example 2:
 * Input: candies = [1,1,2,2,3,3]
 * Output: 3
 * Explanation:
 * There are three different kinds of candies (1, 2 and 3), and two candies for each kind.
 * Optimal distribution: The sister has candies [1,2,3] and the brother has candies [1,2,3].
 * The sister has three different kinds of candies.
 * 
 * Constraints:
 * 1 <= n <= 100000
 * n is even.
 * 1 <= candies[i] <= 100000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int waysToDistribute(int n, int k) {
        const int MOD = 1e9 + 7;
        
        // dp[i][j] = ways to distribute i candies to j bags
        vector<vector<long>> dp(n + 1, vector<long>(k + 1, 0));
        
        // Base cases
        for (int j = 0; j <= k; j++) {
            dp[0][j] = 1;  // 0 candies, 0 ways except j=0?
        }
        
        // 实际上正确的初始化是: dp[0][0] = 1, 其他为0
        // 但为了递推方便，我们采用以下方式
        
        // 重新初始化
        dp[0][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                // 两种选择:
                // 1. 第i个糖果放入一个新的袋子: dp[i-1][j-1]
                // 2. 第i个糖果放入已有的j个袋子中的任意一个: j * dp[i-1][j]
                dp[i][j] = (dp[i-1][j-1] + j * dp[i-1][j]) % MOD;
            }
        }
        
        return dp[n][k] % MOD;
    }
};
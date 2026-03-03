/**
 * 1473. Paint House III
 * 
 * There is a row of m houses in a small city, each house must be painted with one of the n colors (labeled from 1 to n), some houses that have been painted last summer should not be painted again.
 * 
 * A neighborhood is a maximal group of continuous houses that are painted with the same color.
 * 
 * For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods [{1}, {2,2}, {3,3}, {2}, {1,1}].
 * 
 * Given an array houses, an m x n matrix cost and an integer target where:
 * 
 * houses[i]: is the color of the house i, and 0 if the house is not painted yet.
 * cost[i][j]: is the cost of paint the house i with the color j + 1.
 * Return the minimum cost of painting all the remaining houses in such a way that there are exactly target neighborhoods. If it is not possible, return -1.
 * 
 * Example 1:
 * 
 * Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
 * Output: 9
 * Explanation: Paint houses of this way [1,2,2,1,1]
 * This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
 * Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
 * 
 * Example 2:
 * 
 * Input: houses = [0,2,1,2,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
 * Output: 11
 * Explanation: Some houses are already painted, Paint the houses of this way [2,2,1,2,2]
 * This array contains target = 3 neighborhoods, [{2,2}, {1}, {2,2}].
 * Cost of paint all houses (10 + 1 + 1 + 10 + 5) = 11.
 * 
 * Example 3:
 * 
 * Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[1,10],[10,1],[1,10]], m = 5, n = 2, target = 5
 * Output: 5
 * Explanation: Paint houses of this way [1,2,1,2,1]
 * This array contains target = 5 neighborhoods, [{1}, {2,2}, {1}, {2,2}, {1}].
 * Cost of paint all houses (1 + 1 + 1 + 1 + 1) = 5.
 * 
 * Example 4:
 * 
 * Input: houses = [3,1,2,3], cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]], m = 4, n = 3, target = 3
 * Output: -1
 * Explanation: Houses are already painted with a total of 4 neighborhoods [{3},{1},{2},{3}] different of target = 3.
 * 
 * Note:
 * m == houses.length == cost.length
 * n == cost[i].length
 * 1 <= m <= 100
 * 1 <= n <= 20
 * 1 <= target <= m
 * 0 <= houses[i] <= n
 * 1 <= cost[i][j] <= 10^4
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        const int INF = 1e9;
        // dp[i][j][k] = min cost for first i houses, j neighborhoods, i-th house color k
        vector<vector<vector<int>>> dp(m + 1, 
            vector<vector<int>>(target + 1, vector<int>(n + 1, INF)));

        // Base case: first house
        for (int k = 1; k <= n; ++k) {
            if (houses[0] == 0 || houses[0] == k) {
                dp[1][1][k] = (houses[0] == 0) ? cost[0][k - 1] : 0;
            }
        }

        for (int i = 2; i <= m; ++i) {
            for (int j = 1; j <= min(i, target); ++j) {
                for (int k = 1; k <= n; ++k) {
                    // Check if current house can be color k
                    if (houses[i - 1] != 0 && houses[i - 1] != k) continue;
                    int curCost = (houses[i - 1] == 0) ? cost[i - 1][k - 1] : 0;

                    // Transition from previous house
                    for (int p = 1; p <= n; ++p) {
                        if (p == k) {
                            // Same color, same neighborhoods
                            if (dp[i - 1][j][p] != INF)
                                dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][p] + curCost);
                        } else {
                            // Different color, increase neighborhoods by 1
                            if (j > 1 && dp[i - 1][j - 1][p] != INF)
                                dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j - 1][p] + curCost);
                        }
                    }
                }
            }
        }

        int ans = INF;
        for (int k = 1; k <= n; ++k) {
            ans = min(ans, dp[m][target][k]);
        }
        return (ans == INF) ? -1 : ans;
    }
};
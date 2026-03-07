/*
 * 1595. Minimum Cost to Connect Two Groups of Points
 *
 * You are given two groups of points where the first group has size1 points, the second group has size2 points, and size1 >= size2.
 *
 * The cost of the connection between any two points are given in an size1 x size2 matrix where cost[i][j] is the cost of connecting point i of the first group and point j of the second group. The groups are connected if each point in both groups is connected to one or more points in the opposite group. In other words, each point in the first group must be connected to at least one point in the second group, and each point in the second group must be connected to at least one point in the first group.
 *
 * Return the minimum cost it takes to connect the two groups.
 * 
 * Example 1:
 * Input: cost = [[15, 96], [36, 2]]
 * Output: 17
 * Explanation: The optimal way of connecting the groups is:
 * 1--A
 * 2--B
 * This results in a total cost of 17.
 * 
 * Example 2:
 * Input: cost = [[1, 3, 5], [4, 1, 1], [1, 5, 3]]
 * Output: 4
 * Explanation: The optimal way of connecting the groups is:
 * 1--A
 * 2--B
 * 3--C
 * 4--A
 * This results in a total cost of 4.
 * 
 * Example 3:
 * Input: cost = [[2, 5, 1], [3, 4, 7], [8, 1, 2], [6, 2, 4], [3, 8, 8]]
 * Output: 10
 * Explanation: The optimal way of connecting the groups is:
 * 1--A
 * 2--B
 * 3--C
 * 4--A
 * 5--D
 * 6--B
 * 7--C
 * 8--D
 * This results in a total cost of 10.
 * 
 * Constraints:
 * 1 <= size1, size2 <= 12
 * size1 >= size2
 * 0 <= cost[i][j] <= 100
 * 
 */
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        int m = cost.size();       // 第一组的大小 (size1)
        int n = cost[0].size();    // 第二组的大小 (size2)

        // 总共有 2^n 种状态，用二进制位表示第二组每个点是否已连接
        int totalStates = 1 << n;

        // dp[i][mask] 表示处理完第一组的前 i 个点 (0-indexed 表示第 i 个点)，
        // 并且第二组点的连接状态为 mask 时的最小总成本。
        // 初始化 dp 数组为一个很大的数，表示尚未计算或不可达状态
        vector<vector<int>> dp(m + 1, vector<int>(totalStates, INT_MAX / 2));

        // 初始状态：没有处理任何第一组的点 (i=0)，也没有连接任何第二组的点 (mask=0)，成本为 0
        dp[0][0] = 0;

        // 遍历第一组的每一个点，i 从 1 到 m
        for (int i = 1; i <= m; ++i) {
            // 遍历所有可能的连接状态 mask
            for (int mask = 0; mask < totalStates; ++mask) {
                // 尝试将当前点 i-1 (因为第一组的索引从0开始) 连接到第二组的每一个点 j
                for (int j = 0; j < n; ++j) {
                    // 关键优化：我们只考虑那些在当前 mask 中被标记为已连接的点 j
                    // 因为我们最终的目标是所有第二组的点都被连接 (mask 全1)，
                    // 所以合理的状态转移总是通过添加或保留连接来构建 mask。
                    // 这里我们要求 mask 的第 j 位必须是 1。
                    if (!(mask & (1 << j))) {
                        continue;
                    }

                    // 获取当前连接的成本
                    int currentCost = cost[i - 1][j];

                    // 情况 1: 当前点 i-1 只连接了 j，并且 j 之前可能已经被连接过，也可能没被连接过。
                    // 这对应于从 dp[i-1][mask] 转移而来。意味着在连接当前点之前，mask 状态已经存在了（j可能已经被之前的点连接）。
                    dp[i][mask] = min(dp[i][mask], dp[i - 1][mask] + currentCost);

                    // 情况 2: 当前点 i-1 是第一个连接 j 的点。
                    // 这对应于从 dp[i-1][mask ^ (1 << j)] 转移而来。在连接之前，j 位是 0，我们通过当前连接把它变成了 1。
                    dp[i][mask] = min(dp[i][mask], dp[i - 1][mask ^ (1 << j)] + currentCost);

                    // 情况 3: 当前点 i-1 在连接 j 的同时，还允许同一个点 i-1 连接多个第二组的点。
                    // 这对应于从 dp[i][mask ^ (1 << j)] 转移而来。这意味着在处理当前点的过程中，我们已经通过连接其他点（如 j'）达到了 mask ^ (1 << j) 状态，
                    // 现在我们再连接 j，就达到了 mask 状态。这处理了第一组的一个点连接多个第二组点的情况。
                    dp[i][mask] = min(dp[i][mask], dp[i][mask ^ (1 << j)] + currentCost);
                }
            }
        }

        // 最终答案是处理完所有 m 个第一组的点，并且第二组的所有 n 个点都被连接（mask 全为1）时的最小成本
        return dp[m][totalStates - 1];
    }
};
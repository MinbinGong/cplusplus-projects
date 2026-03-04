/**
 * 1548. The Most Similar Path in a Graph
 * 
 * We have n cities and m bi-directional roads where roads[i] = [ai, bi] connects city ai with city bi.
 * Each city has a name consisting of exactly 3 upper-case English letters given in the string array names.
 * Starting at any city x, you can reach any city y where y != x (i.e. the cities and the roads are forming an undirected connected graph).
 * 
 * You will be given the string array targetPath. You should find a path in the graph of the same length and with the minimum edit distance to targetPath.
 * 
 * You need to return the order of the nodes in the path with the minimum edit distance, The path should be of the same length of targetPath and should be valid (i.e. each pair of adjacent nodes in the path should exist in roads).
 * 
 * If there are multiple answers return any one of them.
 * 
 * 
 * Example 1:
 * Input: n = 5, roads = [[0,2],[0,3],[1,2],[1,3],[1,4],[2,4]], names = ["ATL","PEK","LAX","DXB","HND"], targetPath = ["ATL","DXB","HND","LAX"]
 * Output: [0,2,4,2]
 * Explanation: [0,2,4,2], [0,3,0,2] and [0,3,1,2] are accepted answers.
 * [0,2,4,2] is equivalent to ["ATL","LAX","HND","LAX"] which has edit distance = 1 with targetPath.
 * [0,3,0,2] is equivalent to ["ATL","DXB","ATL","LAX"] which has edit distance = 1 with targetPath.
 * [0,3,1,2] is equivalent to ["ATL","DXB","PEK","LAX"] which has edit distance = 1 with targetPath.
 * 
 * Example 2:
 * Input: n = 4, roads = [[1,0],[2,0],[3,0],[2,1],[3,1],[3,2]], names = ["ATL","PEK","LAX","DXB"], targetPath = ["ABC","DEF","GHI","JKL","MNO","PQR","STU","VWX"]
 * Output: [0,1,0,1,0,1,0,1]
 * Explanation: Any path in this graph has edit distance = 8 with targetPath.
 * 
 * Constraints:
 * 2 <= n <= 100
 * m == roads.length
 * n - 1 <= m <= (n * (n - 1) / 2)
 * 0 <= ai, bi <= n - 1
 * ai != bi 
 * The graph is guaranteed to be connected.
 * n == names.length
 * names[i].length == 3
 * names[i] consists of upper-case English letters.
 * There can be two cities with the same name.
 * 1 <= targetPath.length <= 100
 * targetPath[i].length == 3
 * targetPath[i] consists of upper-case English letters.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> mostSimilar(int n, vector<vector<int>>& roads, vector<string>& names, vector<string>& targetPath) {
        // 1. Build graph adjacency list
        vector<int> graph[n];
        for (auto& road : roads) {
            int a = road[0], b = road[1];
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        int m = targetPath.size();
        // dp[i][j] = min edit distance matching first i+1 chars of targetPath ending at city j
        vector<vector<int>> dp(m, vector<int>(n, 1e9));
        // pre[i][j] = previous city that leads to optimal dp[i][j]
        vector<vector<int>> pre(m, vector<int>(n, -1));

        // Initialize first row (i = 0)
        for (int j = 0; j < n; ++j) {
            dp[0][j] = (names[j] != targetPath[0]);
        }

        // Fill DP table
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k : graph[j]) {   // j must be reachable from previous city k
                    int cost = dp[i-1][k] + (names[j] != targetPath[i]);
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                        pre[i][j] = k;
                    }
                }
            }
        }

        // Find best ending city with minimum edit distance
        int bestCity = 0;
        int minDist = dp[m-1][0];
        for (int j = 1; j < n; ++j) {
            if (dp[m-1][j] < minDist) {
                minDist = dp[m-1][j];
                bestCity = j;
            }
        }

        // Backtrack to reconstruct the path
        vector<int> ans(m);
        int cur = bestCity;
        for (int i = m-1; i >= 0; --i) {
            ans[i] = cur;
            cur = pre[i][cur];
        }
        return ans;
    }
};
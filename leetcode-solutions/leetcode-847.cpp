/*
 * 847. Shortest Path Visiting All Nodes
 * 
 * An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.
 * 
 * graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.
 * 
 * Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
 * 
 * Example 1:
 * Input: [[1,2,3],[0],[0],[0]]
 * Output: 4
 * Explanation: One possible path is [1,0,2,0,3]
 * 
 * Example 2:
 * Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
 * Output: 4
 * Explanation: One possible path is [0,1,4,2,3]
 * 
 * Note:
 * 1 <= graph.length <= 12
 * 0 <= graph[i].length < graph.length
 */
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

class Solution1 {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        int fullMask = (1 << n) - 1; // 目标状态：所有节点都已访问

        // visited[u][mask] 表示是否已经到达过 (u, mask) 这个状态
        vector<vector<bool>> visited(n, vector<bool>(1 << n, false));
        // 队列元素：(当前节点, 访问掩码, 当前路径长度)
        queue<tuple<int, int, int>> q;

        // 初始化：可以从任意节点出发
        for (int i = 0; i < n; ++i) {
            int mask = 1 << i;
            q.emplace(i, mask, 0);
            visited[i][mask] = true;
        }

        while (!q.empty()) {
            auto [u, mask, dist] = q.front();
            q.pop();

            // 如果已经访问了所有节点，返回当前路径长度
            if (mask == fullMask) {
                return dist;
            }

            // 遍历当前节点的所有邻居
            for (int v : graph[u]) {
                int newMask = mask | (1 << v); // 更新掩码，标记 v 已被访问
                // 如果这个状态没有被访问过，则入队
                if (!visited[v][newMask]) {
                    visited[v][newMask] = true;
                    q.emplace(v, newMask, dist + 1);
                }
            }
        }
        return -1; // 理论上不会走到这里（图是连通的）
    }
};

// Floyd + 状态压缩 DP 版本
class Solution2 {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        const int INF = 1e9;
        // Floyd 求任意两点间最短距离
        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
            for (int j : graph[i]) {
                dist[i][j] = 1;
            }
        }
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        // dp[mask][i]：已访问 mask，最后在 i 的最短路径
        vector<vector<int>> dp(1 << n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            dp[1 << i][i] = 0;
        }

        for (int mask = 1; mask < (1 << n); ++mask) {
            for (int i = 0; i < n; ++i) {
                if (!(mask & (1 << i))) continue;
                for (int j = 0; j < n; ++j) {
                    if (i == j) continue;
                    int prevMask = mask ^ (1 << i);
                    if (prevMask & (1 << j)) {
                        dp[mask][i] = min(dp[mask][i], dp[prevMask][j] + dist[j][i]);
                    }
                }
            }
        }

        int ans = INF;
        for (int i = 0; i < n; ++i) {
            ans = min(ans, dp[(1 << n) - 1][i]);
        }
        return ans;
    }
};
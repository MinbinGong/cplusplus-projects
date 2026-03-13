/**
 * 1786. Number of Restricted Paths From First to Last Node
 * 
 * There is an undirected weighted connected graph. You are given a positive integer n which denotes that the graph has n nodes labeled from 1 to n, and an array edges where each edges[i] = [ui, vi, weighti] denotes that there is an edge between nodes ui and vi with weight equal to weighti.
 * 
 * A path from node start to node end is a sequence of nodes [z0, z1, z2, ..., zk] such that z0 = start and zk = end and there is an edge between zi and zi+1 where 0 <= i <= k-1.
 * 
 * The distance of a path is the sum of the weights on the edges of the path. Let distanceToLastNode(x) denote the shortest distance of a path between node n and node x. A restricted path is a path that also satisfies that distanceToLastNode(zi) > distanceToLastNode(zi+1) where 0 <= i <= k-1.
 * 
 * Example 1:
 * 
 * Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
 * Output: 3
 * Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three restricted paths are:
 * 1) 1 --> 2 --> 5
 * 2) 1 --> 2 --> 3 --> 5
 * 3) 1 --> 4 --> 5
 * 
 * Example 2:
 * 
 * Input: n = 7, edges = [[1,3,1],[4,1,2],[7,3,4],[2,5,3],[5,6,1],[6,7,2],[7,5,3],[2,6,4]]
 * Output: 1
 * Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The only restricted path is 1 --> 3 --> 7.
 * 
 * Constraints:
 * 
 * 1 <= n <= 2 * 104
 * n - 1 <= edges.length <= 4 * 104
 * edges[i].length == 3
 * 1 <= ui, vi <= n
 * ui != vi
 * 1 <= weighti <= 105
 * There is at most one edge between any two nodes.
 * There is at least one path between any two nodes.
 * 
 * 
 */
#include <vector>
#include <climits>
#include <string>
using namespace std;

class Solution {
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        const int MOD = 1e9 + 7;
        // 构建邻接表
        vector<vector<pair<int, int>>> graph(n + 1);
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }

        // Dijkstra 求所有点到 n 的最短距离
        vector<long long> dist(n + 1, LLONG_MAX);
        dist[n] = 0;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq.emplace(0, n);
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : graph[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.emplace(dist[v], v);
                }
            }
        }

        // 按距离降序排序节点
        vector<int> nodes(n);
        iota(nodes.begin(), nodes.end(), 1);
        sort(nodes.begin(), nodes.end(), [&](int a, int b) {
            return dist[a] > dist[b];
        });

        // DP 计算受限路径数
        vector<int> dp(n + 1, 0);
        dp[n] = 1;
        for (int u : nodes) {
            if (u == n) continue;
            for (auto [v, w] : graph[u]) {
                if (dist[u] > dist[v]) {
                    dp[u] = (dp[u] + dp[v]) % MOD;
                }
            }
        }
        return dp[1];
    }
};
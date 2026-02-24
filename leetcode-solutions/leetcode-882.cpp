/**
 * 882. Reachable Nodes In Subdivided Graph
 *
 * You are given an undirected graph (the "original graph") with n nodes labeled from 0 to n - 1. You decide to subdivide each edge in the graph into a chain of nodes, with the number of new nodes varying between each edge.
 *
 * The graph is given as a 2D array of edges where edges[i] = [ui, vi, cnti] indicates that there is an edge between nodes ui and vi in the original graph, and cnti is the total number of new nodes that you will subdivide the edge into. Note that cnti == 0 means you will not subdivide the edge.
 *
 * To subdivide the edge [ui, vi], replace it with (cnti + 1) new edges and cnti new nodes. The new nodes are x1, x2, ..., xcnti, and the new edges are [ui, x1], [x1, x2], [x2, x3], ..., [xcnti-1, xcnti], [xcnti, vi].
 *
 * Example 1:
 * Input: edges = [[0,1,10],[0,2,1],[1,2,2]]
 * Output: 3
 * Explanation: The graph appears as follows:
 * We start with the 3 edges and reduce each edge to one node.
 * The graph becomes [[0,1],[0,2],[1,2]] like this.
 * We then add back the subdivided edges.
 * The graph now looks like this:
 * We can reach each node from any other node.
 *
 * Example 2:
 * Input: edges = [[0,1,4],[1,2,6],[0,2,8],[1,3,1]]
 * Output: 23
 *
 * Example 3:
 * Input: edges = [[0,1,0]]
 * Output: 0
 *
 * Note:
 * 0 <= edges.length <= 10^4
 * edges[i].length == 3
 * 0 <= ui < vi < n
 * There are no multiple edges in the graph.
 * 0 <= cnti <= 10^4
 * Explanation:
 * The number of nodes in the graph is n - 1.
 * The number of edges in the graph is edges.length.
 * The number of new nodes created in the process is cnti.
 *
 */
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        // 构建邻接表，每条边权值为中间节点数 + 1
        vector<vector<pair<int, long long>>> adj(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1], cnt = e[2];
            long long w = cnt + 1LL;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // Dijkstra 求从 0 到每个原始节点的最短距离
        vector<long long> dist(n, LLONG_MAX);
        dist[0] = 0;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (auto [v, w] : adj[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }

        // 1. 统计可到达的原始节点
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (dist[i] <= maxMoves) ++ans;
        }

        // 2. 统计每条边上可到达的中间节点
        for (auto& e : edges) {
            int u = e[0], v = e[1], cnt = e[2];
            long long rem_u = max(0LL, maxMoves - dist[u]);
            long long rem_v = max(0LL, maxMoves - dist[v]);
            ans += min((long long)cnt, rem_u + rem_v);
        }

        return ans;
    }
};
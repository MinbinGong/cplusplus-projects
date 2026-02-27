/*
 * 1129. Shortest Path with Alternating Colors
 *
 * You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.
 *
 * You are given two arrays redEdges and blueEdges where:
 *
 * redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
 * blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.
 * Return an array answer of length n, where each answer[x] is the length of the shortest path from node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.
 *
 * 1 <= n <= 100
 * 0 <= redEdges.length, blueEdges.length <= 400
 * redEdges[i].length == blueEdges[j].length == 2
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        // 构建邻接表：红色边和蓝色边
        vector<vector<int>> redAdj(n), blueAdj(n);
        for (auto& e : redEdges)  redAdj[e[0]].push_back(e[1]);
        for (auto& e : blueEdges) blueAdj[e[0]].push_back(e[1]);

        // dist[node][color] : 到达 node 且最后一条边颜色为 color 的最短路径长度
        // color 0 表示红色，1 表示蓝色，-1 表示尚未访问
        vector<vector<int>> dist(n, vector<int>(2, -1));
        queue<pair<int, int>> q; // (节点, 最后一条边的颜色)

        // 起点 0 可以看作没有颜色，允许第一步走任意颜色，因此两种状态初始化为 0
        dist[0][0] = dist[0][1] = 0;
        q.push({0, 0});
        q.push({0, 1});

        while (!q.empty()) {
            auto [node, color] = q.front();
            q.pop();
            int nextColor = 1 - color; // 下一步必须走相反颜色
            const auto& edges = (nextColor == 0) ? redAdj : blueAdj; // 根据下一步颜色选择邻接表
            for (int next : edges[node]) {
                if (dist[next][nextColor] == -1) {
                    dist[next][nextColor] = dist[node][color] + 1;
                    q.push({next, nextColor});
                }
            }
        }

        // 对于每个节点，取两种颜色下的最短距离（若均不可达则为 -1）
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            int d0 = dist[i][0], d1 = dist[i][1];
            if (d0 == -1 && d1 == -1) ans[i] = -1;
            else if (d0 == -1) ans[i] = d1;
            else if (d1 == -1) ans[i] = d0;
            else ans[i] = min(d0, d1);
        }
        return ans;
    }
};
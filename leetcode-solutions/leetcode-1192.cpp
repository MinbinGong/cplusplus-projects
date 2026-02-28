/*
 * 1192. Critical Connections in a Network
 *
 * There are n servers numbered from 0 to n-1 connected by undirected server-to-server connections forming a network where connections[i] = [a, b] represents a connection between servers a and b. Any server can reach any other server directly or indirectly through the network.
 * 
 * A critical connection is a connection that, if removed, will make some server unable to reach some other server.
 * 
 * Return all critical connections in the network in any order.
 * 
 * Example 1:
 * Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
 * Output: [[1,3]]
 * Explanation: [[3,1]] is also accepted.
 * 
 * Note:
 * 1 <= n <= 10^5
 * n-1 <= connections.length <= 10^5
 * connections[i][0] != connections[i][1]
 * There are no repeated connections.
 * 
 */
#include <vector>
#include <string>
#include <functional>
using namespace std;

class Solution1 {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // 建立邻接表
        vector<vector<int>> graph(n);
        for (auto& conn : connections) {
            graph[conn[0]].push_back(conn[1]);
            graph[conn[1]].push_back(conn[0]);
        }

        vector<int> disc(n, 0);   // 发现时间
        vector<int> low(n, 0);    // 最早可达时间
        vector<bool> visited(n, false);
        vector<vector<int>> result;
        int time = 0;

        // DFS 函数
        function<void(int, int)> dfs = [&](int u, int parent) {
            visited[u] = true;
            disc[u] = low[u] = ++time;
            for (int v : graph[u]) {
                if (v == parent) continue;           // 忽略父节点
                if (!visited[v]) {
                    dfs(v, u);
                    low[u] = min(low[u], low[v]);
                    // 桥的条件：子节点无法通过其他路径回到 u 或更早
                    if (low[v] > disc[u]) {
                        result.push_back({u, v});
                    }
                } else {
                    // 遇到已访问节点（回边），更新 low 值
                    low[u] = min(low[u], disc[v]);
                }
            }
        };

        // 处理所有连通分量
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i, -1);
            }
        }
        return result;
    }
};
/*
 * Graph Valid Tree
 *
 * Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes),
 * write a function to check whether these edges make up a valid tree.
 */
#include <vector>
#include <functional>
#include <queue>
using namespace std;

// Union-Find 并查集
class Solution1 {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        // 树的边数必须为 n-1
        if (edges.size() != n - 1) return false;

        // 初始化并查集
        vector<int> parent(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }

        // 查找函数（带路径压缩）
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };

        // 遍历每条边
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            int pu = find(u), pv = find(v);

            // 如果两个节点已经在同一个集合中，说明有环
            if (pu == pv) return false;

            // 合并两个集合
            parent[pu] = pv;
        }

        return true;
    }
};

// DFS 检测环
class Solution2 {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false;

        // 构建邻接表
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<bool> visited(n, false);

        // DFS 检测环
        function<bool(int, int)> dfs = [&](int u, int parent) {
            visited[u] = true;
            for (int v : adj[u]) {
                if (v == parent) continue; // 跳过父节点
                if (visited[v]) return false; // 遇到已访问的非父节点 → 有环
                if (!dfs(v, u)) return false;
            }
            return true;
        };

        // 从节点 0 开始 DFS
        if (!dfs(0, -1)) return false;

        // 检查连通性
        for (bool v : visited) {
            if (!v) return false;
        }

        return true;
    }
};

// BFS 检测环
class Solution3 {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false;

        vector<vector<int>> adj(n);
        vector<int> degree(n, 0);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
            degree[e[0]]++;
            degree[e[1]]++;
        }

        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (degree[i] <= 1) q.push(i);
        }

        int visited = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            visited++;
            for (int v : adj[u]) {
                degree[v]--;
                if (degree[v] == 1) q.push(v);
            }
        }

        return visited == n;
    }
};
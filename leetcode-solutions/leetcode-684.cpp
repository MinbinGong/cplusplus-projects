/*
 * Redundant Connection
 *
 * In this problem, a tree is an undirected graph that is connected and has no cycles.
 *
 * The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.
 *
 * The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, that represents an undirected edge connecting nodes u and v.
 *
 * Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array. The answer edge [u, v] should be in the same format, with u < v.
 * 
 * Example 1:
 *
 * Input: [[1,2], [1,3], [2,3]]
 * Output: [2,3]
 * Explanation: The given undirected graph will be like this:
 *   1
 *  / \
 * 2 - 3
 * 
 * Example 2:
 *
 * Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
 * Output: [1,4]
 * Explanation: The given undirected graph will be like this:
 * 5 - 1 - 2
 *     |   |
 *     4 - 3
 * 
 * Note:
 *
 * The size of the input 2D-array will be between 3 and 1000.
 * Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
 * 
 * Follow-up:
 *
 * Can you find a solution which runs in O(N) time?
 * 
 */
 #include <vector>
using namespace std;

// 并查集（Union-Find）
// 时间复杂度：O(N)，其中 N 是节点数（边数等于节点数减一）
// 空间复杂度：O(N)
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size(); // 节点数等于边数
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        // 初始化并查集，每个节点的父节点是自己
        for (int i = 1; i <= n; ++i) parent[i] = i;

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            // 如果 u 和 v 已经连通，则当前边是多余的
            if (find(u) == find(v)) {
                return edge;
            }
            // 否则合并两个集合
            unite(u, v);
        }
        return {}; // 理论上不会执行到这里
    }

private:
    vector<int> parent;
    vector<int> rank;

    // 查找根节点（路径压缩）
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // 合并两个集合（按秩合并）
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};
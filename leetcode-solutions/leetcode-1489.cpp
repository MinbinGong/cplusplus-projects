/**
 * 1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
 * 
 * Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and weighted edge between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.
 * 
 * Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge. On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.
 * 
 * Note that you can return the indices of the edges in any order.
 * 
 * Example 1:
 * Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
 * Output: [[0,1],[2,3,4,5]]
 * Explanation: The figure above describes the graph.
 * The following figure shows all the possible MSTs:
 * 
 * Example 2:
 * Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
 * Output: [[],[0,1,2,3]]
 * Explanation: We can observe that since all 4 edges have equal weight, choosing any 3 edges from the given 4 will yield an MST. Therefore all 4 edges are pseudo-critical.
 * 
 * Constraints:
 * 2 <= n <= 100
 * 1 <= edges.length <= min(200, n * (n - 1) / 2)
 * edges[i].length == 3
 * 0 <= ai < bi < n
 * 1 <= weighti <= 1000
 * All pairs (ai, bi) are distinct.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

class Solution {
public:
    struct Edge {
        int u, v, w, id;
        bool operator<(const Edge& other) const {
            return w < other.w;
        }
    };

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        vector<Edge> e;
        for (int i = 0; i < m; ++i) {
            e.push_back({edges[i][0], edges[i][1], edges[i][2], i});
        }
        sort(e.begin(), e.end());

        // 计算原始最小生成树的权重
        int original = kruskal(n, e, -1, false);

        vector<int> critical, pseudo;
        for (int i = 0; i < m; ++i) {
            // 判断是否为关键边：去掉这条边后 MST 权重变大或无法生成树
            int without = kruskal(n, e, i, false);
            if (without > original) {
                critical.push_back(i);
            } else {
                // 判断是否为伪关键边：强制包含这条边后 MST 权重不变
                int with = kruskal(n, e, i, true);
                if (with == original) {
                    pseudo.push_back(i);
                }
            }
        }
        return {critical, pseudo};
    }

private:
    int kruskal(int n, const vector<Edge>& edges, int targetId, bool include) {
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        };
        auto unite = [&](int x, int y) {
            x = find(x); y = find(y);
            if (x == y) return false;
            parent[x] = y;
            return true;
        };

        int total = 0;
        int cnt = 0;

        if (include) {
            // 强制包含目标边
            bool found = false;
            for (const auto& e : edges) {
                if (e.id == targetId) {
                    if (unite(e.u, e.v)) {
                        total += e.w;
                        cnt++;
                    } else {
                        return INT_MAX;   // 形成环，无法包含
                    }
                    found = true;
                    break;
                }
            }
            if (!found) return INT_MAX;   // 实际上不会发生
        }

        for (const auto& e : edges) {
            if (e.id == targetId) continue;   // 跳过目标边（已处理或排除）
            if (unite(e.u, e.v)) {
                total += e.w;
                cnt++;
            }
        }

        if (cnt != n - 1) return INT_MAX;     // 图不连通
        return total;
    }
};
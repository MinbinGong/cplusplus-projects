/*
 * Redundant Connection II
 * 
 * In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.
 *
 * The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N), with one additional directed edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.
 *
 * The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.
 *
 * Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.
 * 
 * Example 1:
 *
 * Input: [[1,2], [1,3], [2,3]]
 * Output: [2,3]
 * 
 * Example 2:
 *
 * Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
 * Output: [4,1]
 * 
 * Note:
 *
 * The size of the input 2D-array will be between 3 and 1000.
 * Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
 * 
 */
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> indegree(n + 1, 0);
        vector<int> firstParent(n + 1, 0);      // 记录每个节点的第一个父节点
        vector<vector<int>> candidates;          // 存储入度为2时的两条候选边

        // 第一遍扫描：找出入度为2的节点及其对应的两条边
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            indegree[v]++;
            if (indegree[v] == 2) {
                // v 出现了第二个父节点，记录这两条边
                candidates.push_back({firstParent[v], v}); // 较早的那条
                candidates.push_back(e);                   // 当前这条
            } else {
                firstParent[v] = u; // 记录第一个父节点
            }
        }

        // 并查集初始化
        vector<int> parent(n + 1);
        iota(parent.begin(), parent.end(), 0);

        function<int(int)> find = [&](int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        };

        // 情况1：没有入度为2的节点 → 存在环，用并查集找到形成环的最后一条边
        if (candidates.empty()) {
            for (auto& e : edges) {
                int u = e[0], v = e[1];
                int pu = find(u), pv = find(v);
                if (pu == pv) return e;
                parent[pv] = pu;
            }
        } 
        // 情况2：存在入度为2的节点
        else {
            // 先尝试忽略第二条边（较晚出现的那条），检查是否还有环
            for (auto& e : edges) {
                if (e == candidates[1]) continue; // 跳过第二条候选边
                int u = e[0], v = e[1];
                int pu = find(u), pv = find(v);
                if (pu == pv) {
                    // 忽略第二条后仍有环，说明第一条边是冗余的
                    return candidates[0];
                }
                parent[pv] = pu;
            }
            // 忽略第二条后无环，则第二条边是冗余的
            return candidates[1];
        }
        return {}; // 理论上不会执行到这里
    }
};
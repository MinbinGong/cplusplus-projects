/*
 * 1617. Count Subtrees With Max Distance Between Cities    
 *
 * Given n cities numbered from 1 to n. You are given an array edges of size n-1, where edges[i] = [ui, vi] represents a bidirectional edge between cities ui and vi. There exists a unique path between each pair of cities. In other words, the cities form a tree.
 * 
 * A subtree is a subset of cities where every city is reachable from every other city in the subset, where the path between each pair passes through only the cities from the subset. Two subtrees are different if there is a city in one subtree that is not present in the other.
 * 
 * Example 1:
 * Input: n = 4, edges = [[1,2],[2,3],[2,4]]
 * Output: [3,4,4,4]
 * Explanation: The subtrees with subsets {1,2}, {2,3}, {2,4} and {4} have a max distance of 1.
 * The subtrees with subsets {1,2,3}, {1,2,4}, {2,3,4} and {1,2,3,4} have a max distance of 2.
 * Notice that the {2,3} subtree is not counted as it has a max distance of 2.
 * 
 * Example 2:
 * Input: n = 2, edges = [[1,2]]
 * Output: [2]
 * Explanation: The subtree with subsets {1,2} and {2} have a max distance of 1.
 * 
 * Constraints:
 * 2 <= n <= 100
 * 0 <= edges.length <= n * (n - 1) / 2
 * edges[i].length == 2
 * 1 <= ui, vi <= n
 * ui != vi
 * Each pair of cities has at most one road connecting them.
 * 
 */
#include <vector>
#include <functional>
using namespace std;

class Solution {
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        // 构建邻接表（节点编号改为 0-based）
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int a = e[0] - 1, b = e[1] - 1;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        
        vector<int> ans(n - 1, 0);          // 结果数组
        int total = 1 << n;                  // 子集总数
        
        // 枚举所有非空子集（至少两个节点）
        for (int mask = 1; mask < total; ++mask) {
            // 跳过只有一个节点的子集（直径至少为1）
            if ((mask & (mask - 1)) == 0) continue;
            
            int vis = 0;                     // 本次DFS已访问节点
            int diameter = 0;                 // 当前子集的直径
            
            // 树形DP求直径，返回以u为根的子树深度
            function<int(int)> dfs = [&](int u) -> int {
                vis |= (1 << u);               // 标记u已访问
                int max_depth = 0;              // 当前节点的最大深度
                for (int v : g[u]) {
                    // v必须在子集中且未访问
                    if ((mask >> v & 1) && !(vis >> v & 1)) {
                        int child_depth = dfs(v) + 1;
                        // 更新直径：经过u的最长路径 = 当前最大深度 + 子节点深度
                        diameter = max(diameter, max_depth + child_depth);
                        max_depth = max(max_depth, child_depth);
                    }
                }
                return max_depth;
            };
            
            // 找到mask中最低位的1作为起点
            int start = __builtin_ctz(mask);
            dfs(start);
            
            // 如果访问到的节点数等于mask中的节点数，说明是连通子树
            if (vis == mask) {
                ++ans[diameter - 1];
            }
        }
        return ans;
    }
};
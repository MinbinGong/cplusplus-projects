/*
 * 1168. Optimize Water Distribution in a Village
 * 
 * There are n houses in a village. We want to supply water for all the houses by building wells and laying pipes.
 * 
 * For each house i, we can either build a well inside it directly with cost wells[i - 1] (note the -1 due to 0-indexing), or pipe in water from another well to it. The costs to lay pipes between houses are given by the array pipes, where each pipes[j] = [house1j, house2j, costj] represents the cost to connect house1j and house2j together using a pipe. Connections are bidirectional.
 * 
 * Return the minimum total cost to supply water to all houses.
 * 
 * Example 1:
 * Input: n = 3, wells = [1,2,2], pipes = [[1,2,1],[2,3,1]]
 * Output: 3
 * Explanation: 
 * The image shows the costs of connecting houses using pipes.
 * 
 * Example 2:
 * Input: n = 2, wells = [1,1], pipes = [[1,2,1],[1,2,2]]
 * Output: 2
 * Explanation: 
 * We can supply water with cost two using one of the three options:
 * Option 1:
 *   - Build a well inside house 1 with cost 1.
 *   - Build a well inside house 2 with cost 1.
 *   - Connect house 1 and house 2 with pipe with cost 1.
 * Option 2:
 *   - Build a well inside house 1 with cost 1.
 *   - Connect house 2 with house 1 with pipe with cost 1.
 * Option 3:
 *   - Build a well inside house 2 with cost 1.
 *   - Connect house 1 with house 2 with pipe with cost 1.
 * Note that we can connect houses 1 and 2 with pipe or build wells inside them with cost 2 but we will get the minimum cost if we choose option 1 or option 2.
 * 
 * Note:
 * 1 <= n <= 10^4
 * wells.length == n
 * 0 <= wells[i] <= 10^5
 * 1 <= pipes.length <= 10^4
 * pipes[j].length == 3
 * 1 <= house1j, house2j <= n
 * 0 <= costj <= 10^5
 * house1j != house2j
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        // 并查集数据结构，用于管理节点的连通性
        vector<int> parent(n + 1); // 节点编号从 0 到 n
        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
        }

        // 查找操作（带路径压缩）
        function<int(int)> find = [&](int x) -> int {
            if (x != parent[x]) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };

        // 构建所有边的列表
        vector<vector<int>> edges = pipes; // 先复制已有的管道

        // 将“打井”成本转化为从虚拟节点 0 到各个房屋的边
        for (int i = 1; i <= n; ++i) {
            edges.push_back({0, i, wells[i - 1]});
        }

        // 按边的权重（成本）从小到大排序，这是 Kruskal 算法的关键
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        int totalCost = 0;
        int edgesUsed = 0; // 记录已使用的边数，用于提前终止循环

        // Kruskal 算法主循环
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];

            int rootU = find(u);
            int rootV = find(v);

            // 如果这条边连接的两个节点尚未连通，则选择它
            if (rootU != rootV) {
                totalCost += cost;
                parent[rootU] = rootV; // 合并两个集合
                edgesUsed++;
                // 对于 n+1 个节点的图，最小生成树有 n 条边
                if (edgesUsed == n) {
                    break;
                }
            }
        }

        return totalCost;
    }
};
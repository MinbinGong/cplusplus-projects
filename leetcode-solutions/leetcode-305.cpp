/*
 * Number of Islands II
 *
 * A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
 * 
 * Example:
 * Input: m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]]
 * Output: [1,1,2,3]
 * Explanation:
 * Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).
 * 
 * 0 0 0
 * 0 0 0
 * 0 0 0
 * Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.
 * 1 0 0
 * 0 0 0
 * 0 0 0
 * Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.
 * 1 1 0
 * 0 0 0
 * 0 0 0
 * Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.
 * 1 1 0
 * 0 0 1
 * 0 0 0
 * Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.
 * 1 1 0
 * 0 0 1
 * 0 1 0
 * 
 */
#include <vector>
#include <functional>
using namespace std;

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        vector<int> res;
        vector<int> parent(m * n, -1); // -1 表示该位置还是水
        int cnt = 0; // 当前岛屿数量
        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // 查找函数（带路径压缩）
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };

        // 合并函数，返回是否成功合并
        auto unite = [&](int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX == rootY) return false;
            parent[rootX] = rootY;
            return true;
        };

        for (auto& pos : positions) {
            int r = pos[0], c = pos[1];
            int idx = r * n + c; // 二维转一维

            // 如果已经是陆地（可能重复操作），直接记录当前岛屿数
            if (parent[idx] != -1) {
                res.push_back(cnt);
                continue;
            }

            // 新增陆地，先标记自己为岛屿
            parent[idx] = idx;
            cnt++;

            // 检查四个方向的邻居
            for (auto [dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;
                int nidx = nr * n + nc;
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && parent[nidx] != -1) {
                    // 如果当前新岛屿与邻居岛屿成功合并，则岛屿总数减少
                    if (unite(idx, nidx)) {
                        cnt--;
                    }
                }
            }
            res.push_back(cnt);
        }
        return res;
    }
};
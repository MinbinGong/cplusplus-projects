/*
 * Number of Distinct Islands II
 *
 * Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
 * 
 * Example 1:
 *
 * Input: grid = [[1,1,0,0,0],[1,0,0,0,0],[0,0,0,0,1],[0,0,0,1,1]]
 * Output: 3
 * 
 * Explanation:
 * The 3 islands are shown in the image.
 * 
 * Note:
 * 1. The length of each dimension in the given grid does not exceed 50.
 * 2. The number of islands in the given grid is between [1, 6000].
 * 3. The number of distinct islands is between [1, 6000].
 * 4. The number of distinct islands is the number of unique shapes that have at least one 1 in the grid.
 * 
 */
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    int numDistinctIslands2(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        set<vector<pair<int, int>>> uniqueIslands;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    vector<pair<int, int>> shape;
                    // DFS 遍历岛屿，记录相对坐标
                    dfs(grid, i, j, i, j, shape);
                    // 获取岛屿的规范化形态，并加入集合
                    uniqueIslands.insert(normalize(shape));
                }
            }
        }
        return uniqueIslands.size();
    }

private:
    void dfs(vector<vector<int>>& grid, int x, int y, int baseX, int baseY, vector<pair<int, int>>& shape) {
        int m = grid.size(), n = grid[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != 1) return;

        // 标记为已访问，并记录相对坐标
        grid[x][y] = 0;
        shape.emplace_back(x - baseX, y - baseY);

        // 四个方向递归
        dfs(grid, x + 1, y, baseX, baseY, shape);
        dfs(grid, x - 1, y, baseX, baseY, shape);
        dfs(grid, x, y + 1, baseX, baseY, shape);
        dfs(grid, x, y - 1, baseX, baseY, shape);
    }

    // 规范化函数：生成8种变换，选择并返回最小的作为规范形态
    vector<pair<int, int>> normalize(vector<pair<int, int>>& shape) {
        vector<vector<pair<int, int>>> allShapes(8);

        // 1. 生成所有8种变换
        for (auto& p : shape) {
            int x = p.first, y = p.second;
            allShapes[0].emplace_back(x, y);
            allShapes[1].emplace_back(x, -y);
            allShapes[2].emplace_back(-x, y);
            allShapes[3].emplace_back(-x, -y);
            allShapes[4].emplace_back(y, x);
            allShapes[5].emplace_back(y, -x);
            allShapes[6].emplace_back(-y, x);
            allShapes[7].emplace_back(-y, -x);
        }

        // 2. 对每种变换进行规范化
        for (auto& s : allShapes) {
            // 排序
            sort(s.begin(), s.end());
            // 平移到原点
            int minX = s[0].first, minY = s[0].second;
            for (auto& point : s) {
                point.first -= minX;
                point.second -= minY;
            }
        }

        // 3. 对所有变换的规范形态进行排序，选择最小的作为最终代表
        sort(allShapes.begin(), allShapes.end());
        return allShapes[0];
    }
};
/*
 * Number of Distinct Islands
 *
 * Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) 
 * You may assume all four edges of the grid are surrounded by water.
 * 
 * Count the number of distinct islands. An island is considered to be the same as another if and only if one island can be translated (and not rotated or reflected) to equal the other.
 * 
 * Example 1:
 * 11000
 * 11000
 * 00011
 * 00011
 * Given the above grid map, return 1.
 * 
 * Example 2:
 * 11011
 * 10000
 * 00001
 * 11011
 * Given the above grid map, return 3.
 * 
 * Note:
 * The length of each dimension in the given grid does not exceed 50.
 * 
 */
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        set<vector<pair<int, int>>> islands;  // 存储每个岛屿的形状（相对坐标列表）
        
        // 方向数组：上下左右
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    vector<pair<int, int>> shape;
                    dfs(grid, visited, i, j, i, j, shape, dirs);
                    islands.insert(shape);
                }
            }
        }
        return islands.size();
    }
    
private:
    void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited,
             int x, int y, int baseX, int baseY, 
             vector<pair<int, int>>& shape, int dirs[4][2]) {
        int m = grid.size(), n = grid[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n) return;
        if (grid[x][y] != 1 || visited[x][y]) return;
        
        visited[x][y] = true;
        // 记录相对于基准点的偏移
        shape.emplace_back(x - baseX, y - baseY);
        
        for (auto& d : dirs) {
            int nx = x + d[0], ny = y + d[1];
            dfs(grid, visited, nx, ny, baseX, baseY, shape, dirs);
        }
    }
};
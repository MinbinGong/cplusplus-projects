/*
 * 1568. Minimum Number of Days to Disconnect Island
 * 
 * Given a 2D grid consisting of 1s (land) and 0s (water).  An island is a maximal 4-directionally (horizontal or vertical) connected group of 1s.
 * 
 * The grid is said to be connected if we have exactly one island, otherwise is said disconnected.
 * 
 * In one day, we are allowed to change any single land cell (1) into a water cell (0).
 * 
 * Return the minimum number of days to disconnect the grid.
 * 
 * Example 1:
 * Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
 * Output: 2
 * Explanation: We need at least 2 days to get a disconnected grid.
 * 
 * Example 2:
 * Input: grid = [[1,1]]
 * Output: 2
 * Explanation: Grid of full water is also disconnected ([[1,1]] -> [[0,0]]), 0 islands.
 * 
 * Example 3:
 * Input: grid = [[1,0,1,0]]
 * Output: 0
 * 
 * Constraints:
 * 1 <= grid.length, grid[i].length <= 30
 * grid[i][j] is 0 or 1.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int minDays(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // 如果初始岛屿数量不为1，则已经分离
        if (countIslands(grid) != 1) return 0;

        // 尝试移除每一个陆地
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0; // 移除
                    if (countIslands(grid) != 1) {
                        return 1;   // 移除后不再是一个岛
                    }
                    grid[i][j] = 1; // 恢复
                }
            }
        }
        return 2; // 否则需要两天
    }

private:
    int countIslands(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    ++count;
                    dfs(grid, visited, i, j);
                }
            }
        }
        return count;
    }

    void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0 || visited[i][j])
            return;
        visited[i][j] = true;
        dfs(grid, visited, i + 1, j);
        dfs(grid, visited, i - 1, j);
        dfs(grid, visited, i, j + 1);
        dfs(grid, visited, i, j - 1);
    }
};

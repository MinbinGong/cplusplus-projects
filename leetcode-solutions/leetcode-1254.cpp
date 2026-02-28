/*
 * 1254. Number of Closed Islands
 *
 * Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.
 *
 * Return the number of closed islands.
 *
 * Example 1:
 * Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
 * Output: 2
 * Explanation: 
 * Islands in gray are closed because they are completely surrounded by water (group of 1s).
 *
 * Example 2:
 * Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
 * Output: 1
 *
 * Example 3:
 * Input: grid = [[1,1,1,1,1,1,1],
 *                [1,0,0,0,0,0,1],
 *                [1,0,1,1,1,0,1],
 *                [1,0,1,0,1,0,1],
 *                [1,0,1,1,1,0,1],
 *                [1,0,0,0,0,0,1],
 *                [1,1,1,1,1,1,1]]
 * Output: 2
 *
 * Constraints:
 * 1 <= grid.length, grid[0].length <= 100
 * 0 <= grid[i][j] <=1
 * 
 */
#include <vector>
#include <functional>

class Solution {
public:
    int closedIsland(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();

        // Depth‑first search to mark all land connected to (i, j)
        std::function<void(int, int)> dfs = [&](int i, int j) {
            if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != 0)
                return;
            grid[i][j] = 1;          // mark as water (visited)
            dfs(i + 1, j);
            dfs(i - 1, j);
            dfs(i, j + 1);
            dfs(i, j - 1);
        };

        // Invalidate all land that touches the border
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == 0) dfs(i, 0);
            if (grid[i][n - 1] == 0) dfs(i, n - 1);
        }
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == 0) dfs(0, j);
            if (grid[m - 1][j] == 0) dfs(m - 1, j);
        }

        // Count the remaining closed islands
        int count = 0;
        for (int i = 1; i < m - 1; ++i) {
            for (int j = 1; j < n - 1; ++j) {
                if (grid[i][j] == 0) {
                    ++count;
                    dfs(i, j);       // erase this whole island
                }
            }
        }
        return count;
    }
};
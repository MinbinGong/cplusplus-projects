/**
 * 1219. Path with Maximum Gold
 *
 * In a gold mine grid of size m * n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.
 *
 * Return the maximum amount of gold you can collect under the conditions:
 *
 * Every time you are located in a cell you will collect all the gold in that cell.
 * From your position you can walk one step to the left, right, up or down.
 * You can't visit the same cell more than once.
 * Never visit a cell with 0 gold.
 * You can start and stop collecting gold from any position in the grid that has some gold.
 *
 *
 * Example 1:
 *
 * Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
 * Output: 24
 * Explanation:
 * [[0,6,0],
 *  [5,8,7],
 *  [0,9,0]]
 * Path to get the maximum gold, 9 -> 8 -> 7.
 *
 * Example 2:
 *
 * Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
 * Output: 28
 * Explanation:
 * [[1,0,7],
 *  [2,0,6],
 *  [3,4,5],
 *  [0,3,0],
 *  [9,0,20]]
 * Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.
 * 
 * Note:
 *
 * 1 <= grid.length, grid[i].length <= 15
 * 0 <= grid[i][j] <= 100
 * There are at most 25 cells containing gold.
 *
 */
#include <vector>
#include <algorithm>

class Solution {
public:
    int getMaximumGold(std::vector<std::vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        int maxGold = 0;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 0) {
                    maxGold = std::max(maxGold, dfs(grid, visited, i, j));
                }
            }
        }
        
        return maxGold;
    }
    
private:
    int dfs(std::vector<std::vector<int>>& grid, std::vector<std::vector<bool>>& visited, 
            int i, int j) {
        int m = grid.size(), n = grid[0].size();
        
        // 检查边界条件，是否为0，是否已访问
        if (i < 0 || i >= m || j < 0 || j >= n || 
            grid[i][j] == 0 || visited[i][j]) {
            return 0;
        }
        
        visited[i][j] = true;
        int current = grid[i][j];
        
        // 向四个方向进行DFS
        int up = dfs(grid, visited, i-1, j);
        int down = dfs(grid, visited, i+1, j);
        int left = dfs(grid, visited, i, j-1);
        int right = dfs(grid, visited, i, j+1);
        
        visited[i][j] = false;  // 回溯
        
        // 返回当前单元格的值加上四个方向的最大值
        return current + std::max({up, down, left, right});
    }
};
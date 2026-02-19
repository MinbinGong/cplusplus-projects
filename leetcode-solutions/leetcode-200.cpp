/*
 * Number of Islands
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
 * 
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
 * 
 * Constraints:
 * 1. m == grid.length
 * 2. n == grid[i].length
 * 3. 1 <= m, n <= 300
 * 4. grid[i][j] is '0' or '1'.
 */
#include <vector>
using namespace std;

void dfs(vector<vector<int>> &grid, int r, int c) {
  int nr = grid.size();
  int nc = grid[0].size();

  grid[r][c] = '0';
  if (r - 1 >= 0 && grid[r - 1][c] == '1') {
    dfs(grid, r - 1, c);
  }

  if (r + 1 < nr && grid[r + 1][c] == '1') {
    dfs(grid, r + 1, c);
  }

  if (c - 1 >= 0 && grid[r][c - 1] == '1') {
    dfs(grid, r, c - 1);
  }

  if (c + 1 < nc && grid[r][c + 1] == '1') {
    dfs(grid, r, c + 1);
  }
}

int numIslands(vector<vector<int>> &grid) {
  int nr = grid.size();
  if (nr <= 0) {
    return 0;
  }

  int nc = grid[0].size();
  int num_islands = 0;
  for (int r = 0; r < nr; r++) {
    for (int c = 0; c < nc; c++) {
      if (grid[r][c] == '1') {
        num_islands++;
        dfs(grid, r, c);
      }
    }
  }
  return num_islands;
}
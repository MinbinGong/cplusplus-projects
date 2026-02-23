/*
 * Maximum Area of Island
 * 
 * Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
 * 
 * Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)
 * 
 * Example 1:
 * 
 * [[0,0,1,0,0,0,0,1,0,0,0,0,0],
 *  [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *  [0,1,1,0,1,0,0,0,0,0,0,0,0],
 *  [0,1,0,0,1,1,0,0,1,0,1,0,0],
 *  [0,1,0,0,1,1,0,0,1,1,1,0,0],
 * 
 * Example 2:
 * 
 * [[0,0,0,0,0,0,0,0]]
 * 
 * Example 3:
 * 
 * [[1,1,0,0,0],
 *  [1,1,0,0,0],
 *  [0,0,0,1,1],
 *  [0,0,0,1,1]]
 * 
 * Example 4:
 * 
 * [[1,1,0,1,1],
 *  [1,0,0,0,0],
 *  [0,0,0,0,1],
 *  [1,1,0,1,1]]
 * 
 * Example 5:
 * 
 * [[1,1,0,1,1],
 *  [1,1,0,1,1],
 *  [0,0,0,0,0],
 *  [0,0,0,0,0]]
 * 
 * Note:
 * 
 * The length of each dimension in the given grid does not exceed 50.
 * 
 */
#include <stack>
#include <utility>
#include <vector>
using namespace std;

const vector<int> direction{-1, 0, 1, 0, -1};

int maxAreaOfIsland(vector<vector<int>> &grid) {
  int m = grid.size(), n = m == 0 ? 0 : grid[0].size();
  int area = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 0) {
        continue;
      }

      int local_area = 1;
      grid[i][j] = 0;
      stack<pair<int, int>> island;
      island.push({i, j});
      while (!island.empty()) {
        auto [r, c] = island.top();
        island.pop();
        for (int k = 0; k < 4; k++) {
          int x = r + direction[k], y = c + direction[k + 1];
          if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1) {
            grid[x][y] = 0;
            ++local_area;
            island.push({x, y});
          }
        }
      }
      area = max(area, local_area);
    }
  }

  return area;
}

int dfs1(vector<vector<int>> &grid, int r, int c) {
  if (grid[r][c] == 0) {
    return 0;
  }

  grid[r][c] = 0;
  int area = 1;
  for (int i = 0; i < 4; ++i) {
    int x = r + direction[i], y = c + direction[i + 1];
    if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1) {
      area += dfs(grid, x, y);
    }
  }
  return area;
}

int maxAreaOfIsland1(vector<vector<int>> &grid) {
  if (grid.empty() || grid[0].empty()) {
    return 0;
  }

  int max_area = 0;
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].size(); ++j) {
      if (grid[i][j] == 1) {
        max_area = max(max_area, dfs1(grid, i, j));
      }
    }
  }
  return max_area;
}

int dfs2(vector<vector<int>> &grid, int r, int c) {
  if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] == 0) {
    return 0;
  }
  grid[r][c] = 0;
  return 1 + dfs2(grid, r + 1, c) + dfs2(grid, r - 1, c) + dfs2(grid, r, c + 1) + dfs2(grid, r, c - 1);
}

int maxAreaOfIsland2(vector<vector<int>> &grid) {
  if (grid.empty() || grid[0].empty()) {
    return 0;
  }
  int max_area = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      max_area = max(max_area, dfs2(grid, i, j));
    }
  }
  return max_area;
}
/*
 * Shortest Bridge
 *
 * In a given 2D binary array grid, there are two islands.  (An island is a 4-directionally connected group of 1s not connected to any other 1s.)
 * We may flip 0s to 1s so as to connect the two islands together to form 1 island.
 * 
 * Return the smallest number of 0s that must be flipped.  (It is guaranteed that the answer is at least 1.)
 * 
 * Example 1:
 * Input: grid = [[0,1],[1,0]]
 * Output: 1
 * 
 * Example 2:
 * Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
 * Output: 2
 * 
 * Example 3:
 * Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
 * Output: 1
 * 
 * Note:
 * 1 <= grid.length = grid[0].length <= 100
 * grid[i][j] == 0 or grid[i][j] == 1
 * 
 */
#include <queue>
#include <utility>
#include <vector>
using namespace std;

vector<int> direction{-1, 0, 1, 0, -1};

void dfs(queue<pair<int, int>>& points, vector<vector<int>>& grid, int m, int n, int i, int j) {
  if (i < 0 || j < 0 || i == m || j == n || grid[i][j] == 2) {
    return;
  }
  if (grid[i][j] == 0) {
    points.push({i, j});
    return;
  }

  grid[i][j] = 2;
  dfs(points, grid, m, n, i - 1, j);
  dfs(points, grid, m, n, i + 1, j);
  dfs(points, grid, m, n, i, j - 1);
  dfs(points, grid, m, n, i, j + 1);
}

int shortestBridge(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  queue<pair<int, int>> points;
  bool flipped = false;
  for (int i = 0; i < m; ++i) {
    if (flipped) {
      break;
    }
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == 0) {
        continue;
      }

      dfs(points, grid, m, n, i, j);
      flipped = true;
      break;
    }
  }

  int x, y;
  int level = 0;
  while (!points.empty()) {
    ++level;
    int n_points = points.size();
    while (n_points--) {
      auto [r, c] = points.front();
      points.pop();
      for (int k = 0; k < 4; k++) {
        x = r + direction[k], y = c + direction[k + 1];
        if (x >= 0 && y >= 0 && x < m && y < n) {
          if (grid[x][y] == 2) {
            continue;
          }
          if (grid[x][y] == 1) {
            return level;
          }
          points.push({x, y});
          grid[x][y] = 2;
        }
      }
    }
  }
  return 0;
}
/*
 * Island Perimeter
 *
 * You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
 *
 * Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
 *
 * The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.
 *
 * Constraints:
 * row == grid.length
 * col == grid[i].length
 * 1 <= row, col <= 100
 * grid[i][j] is 0 or 1.
 * There is exactly one island in grid.
 * 
 */
#include <vector>
using namespace std;

int islandPerimeter(vector<vector<int>> &grid) {
  int res = grid[0][0] ? 4 : 0;

  for (int j = 1; j < grid[0].size(); ++j)
    if (grid[0][j]) {
      if (grid[0][j - 1])
        res += 2;
      else
        res += 4;
    }

  for (int i = 1; i < grid.size(); ++i)
    if (!grid[i][0])
      continue;
    else if (grid[i - 1][0])
      res += 2;
    else
      res += 4;

  for (int i = 1; i < grid.size(); ++i) {
    for (int j = 1; j < grid[0].size(); ++j) {
      if (!grid[i][j])
        continue;
      else if (grid[i][j - 1] && grid[i - 1][j])
        ;
      else if (grid[i][j - 1] || grid[i - 1][j])
        res += 2;
      else
        res += 4;
    }
  }
  return res;
}
/*
 * 1034. Coloring A Border
 *
 * Given a 2-dimensional grid of integers, each value in the grid represents the color of the grid square at that location.
 *
 * Two squares belong to the same connected component if and only if they have the same color and are next to each other in any of the 4 directions.
 *
 * The border of a connected component is all the squares in the connected component that are either 4-directionally adjacent to a square not in the component, or on the boundary of the grid (the first or last row or column).
 *
 * Given a square at location (r0, c0) in the grid and a color, color the border of the connected component of that square with the given color, and return the final grid.
 * 
 * Example 1:
 *
 * Input: grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
 * Output: [[3, 3], [3, 2]]
 * 
 * Example 2:
 *
 * Input: grid = [[1,2,2],[2,3,2]], r0 = 0, c0 = 1, color = 3
 * Output: [[1, 3, 3], [2, 3, 3]]
 * 
 * Example 3:
 *
 * Input: grid = [[1,1,1],[1,1,1],[1,1,1]], r0 = 1, c0 = 1, color = 2
 * Output: [[2, 2, 2], [2, 1, 2], [2, 2, 2]]
 * 
 * Note:
 * 1 <= grid.length <= 50
 * 1 <= grid[0].length <= 50
 * 1 <= grid[i][j] <= 1000
 * 0 <= r0 < grid.length
 * 0 <= c0 < grid[0].length
 * 1 <= color <= 1000
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
        int m = grid.size(), n = grid[0].size();
        int orig = grid[r0][c0];
        if (orig == color) return grid;               // nothing to change

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pair<int, int>> component;

        // collect all cells of the connected component
        dfs(grid, r0, c0, orig, visited, component);

        // recolor border cells
        for (auto [x, y] : component) {
            // cell on the grid boundary -> border
            if (x == 0 || x == m - 1 || y == 0 || y == n - 1) {
                grid[x][y] = color;
                continue;
            }
            // cell adjacent to a cell of different color -> border
            if (grid[x - 1][y] != orig || grid[x + 1][y] != orig ||
                grid[x][y - 1] != orig || grid[x][y + 1] != orig) {
                grid[x][y] = color;
            }
        }
        return grid;
    }

private:
    void dfs(const vector<vector<int>>& grid, int x, int y, int orig,
             vector<vector<bool>>& visited, vector<pair<int, int>>& comp) {
        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size()) return;
        if (visited[x][y] || grid[x][y] != orig) return;

        visited[x][y] = true;
        comp.emplace_back(x, y);

        dfs(grid, x + 1, y, orig, visited, comp);
        dfs(grid, x - 1, y, orig, visited, comp);
        dfs(grid, x, y + 1, orig, visited, comp);
        dfs(grid, x, y - 1, orig, visited, comp);
    }
};
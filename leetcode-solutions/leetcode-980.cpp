/**
 * 980. Unique Paths III
 *
 * On a 2-dimensional grid, there are 4 types of squares:
 *
 * 1 represents the starting square.  There is exactly one starting square.
 * 2 represents the ending square.  There is exactly one ending square.
 * 0 represents empty squares we can walk over.
 * -1 represents obstacles that we cannot walk over.
 * Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.
 *
 * Example 1:
 *
 * Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
 * Output: 2
 * Explanation: We have the following two paths:
 * 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
 * 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
 * 
 * Example 2:
 *
 * Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
 * Output: 4
 * Explanation: We have the following four paths:
 * 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
 * 2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
 * 3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
 * 4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
 * 
 * Example 3:
 *
 * Input: [[0,1],[2,0]]
 * Output: 0
 * Explanation: 
 * There is no path that walks over every empty square exactly once.
 * Note that the starting and ending square can be anywhere in the grid.
 * 
 * Note:
 *
 * 1 <= grid.length * grid[0].length <= 20
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int start_r, start_c;
        int total = 0; // number of walkable cells (1, 2, and all 0's)

        // locate start and count walkable cells
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != -1) ++total;
                if (grid[i][j] == 1) {
                    start_r = i;
                    start_c = j;
                }
            }
        }

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int ans = 0;
        visited[start_r][start_c] = true;
        dfs(grid, visited, start_r, start_c, 1, total, ans);
        return ans;
    }

private:
    void dfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited,
             int r, int c, int count, int total, int& ans) {
        // if we have reached the end cell
        if (grid[r][c] == 2) {
            if (count == total) ++ans;
            return; // cannot go further from end
        }

        // explore four neighbours
        const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int m = grid.size();
        int n = grid[0].size();

        for (auto& d : dirs) {
            int nr = r + d[0];
            int nc = c + d[1];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                !visited[nr][nc] && grid[nr][nc] != -1) {
                visited[nr][nc] = true;
                dfs(grid, visited, nr, nc, count + 1, total, ans);
                visited[nr][nc] = false;
            }
        }
    }
};
/**
 * 1391. Check if There is a Valid Path in a Grid
 * 
 * Given a m x n grid. Each cell of the grid represents a street. The street of grid[i][j] can be:
 * 1 which means a street connecting the left cell and the right cell.
 * 2 which means a street connecting the upper cell and the lower cell.
 * 3 which means a street connecting the left cell and the lower cell.
 * 4 which means a street connecting the right cell and the lower cell.
 * 5 which means a street connecting the left cell and the upper cell.
 * 6 which means a street connecting the right cell and the upper cell.
 * 
 * You will initially start at the street of the upper-left cell (0,0). A valid path in the grid is a path which starts from the upper left cell (0,0) and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.
 * 
 * Notice that you are not allowed to change any street.
 * 
 * Example 1:
 * Input: grid = [[2,4,3],[6,5,2]]
 * Output: true
 * Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
 * 
 * Example 2:
 * Input: grid = [[1,2,1],[1,2,1]]
 * Output: false
 * Explanation: As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get stuck at cell (0, 0)
 * 
 * Example 3:
 * Input: grid = [[1,1,2]]
 * Output: false
 * Explanation: You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).
 * 
 * Example 4:
 * Input: grid = [[1,1,1,1,1,1,3]]
 * Output: true
 * Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
 * 
 * Example 5:
 * Input: grid = [[2],[2],[2],[2],[2],[2],[6]]
 * Output: true
 * Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
 * 
 * Note:
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 300
 * 1 <= grid[i][j] <= 6
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // allowed[pipe_type][direction] = true if pipe has opening in that direction
        // directions: 0: up, 1: right, 2: down, 3: left
        bool allowed[7][4] = {false};
        // pipe 1: left-right
        allowed[1][1] = true;  // right
        allowed[1][3] = true;  // left
        // pipe 2: up-down
        allowed[2][0] = true;  // up
        allowed[2][2] = true;  // down
        // pipe 3: left-down
        allowed[3][2] = true;  // down
        allowed[3][3] = true;  // left
        // pipe 4: right-down
        allowed[4][1] = true;  // right
        allowed[4][2] = true;  // down
        // pipe 5: left-up
        allowed[5][0] = true;  // up
        allowed[5][3] = true;  // left
        // pipe 6: right-up
        allowed[6][0] = true;  // up
        allowed[6][1] = true;  // right

        // BFS
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int,int>> q;
        q.push({0,0});
        visited[0][0] = true;

        int dirs[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}}; // up, right, down, left
        int opposite[4] = {2,3,0,1}; // opposite direction: up<->down, right<->left

        while (!q.empty()) {
            auto [i,j] = q.front(); q.pop();
            if (i == m-1 && j == n-1) return true;

            int curPipe = grid[i][j];
            for (int d = 0; d < 4; ++d) {
                // if current pipe does not have opening in direction d, skip
                if (!allowed[curPipe][d]) continue;

                int ni = i + dirs[d][0];
                int nj = j + dirs[d][1];
                if (ni < 0 || ni >= m || nj < 0 || nj >= n) continue;
                if (visited[ni][nj]) continue;

                int nextPipe = grid[ni][nj];
                int opp = opposite[d]; // direction from neighbor to current cell
                if (allowed[nextPipe][opp]) {
                    visited[ni][nj] = true;
                    q.push({ni,nj});
                }
            }
        }
        return false;
    }
};
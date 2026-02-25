/*
 * 1020. Number of Enclaves
 *
 * Given a 2D array A, each cell is 0 (representing sea) or 1 (representing land)
 *
 * A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.
 *
 * Return the number of land squares in the grid for which we cannot walk off the boundary of the grid in any number of moves.
 * 
 * Example 1:
 *
 * Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
 * Output: 3
 * Explanation: 
 * There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.
 * 
 * Example 2:
 *
 * Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
 * Output: 0
 * Explanation: 
 * All 1s are either on the boundary or can reach the boundary.
 * 
 * Note:
 *
 * 1 <= A.length <= 500
 * 1 <= A[i].length <= 500
 * 0 <= A[i][j] <= 1
 * All rows have the same size.
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        
        // Push all boundary land cells into the queue and mark them as water (0)
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == 1) {
                q.push({i, 0});
                grid[i][0] = 0;
            }
            if (grid[i][n - 1] == 1) {
                q.push({i, n - 1});
                grid[i][n - 1] = 0;
            }
        }
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == 1) {
                q.push({0, j});
                grid[0][j] = 0;
            }
            if (grid[m - 1][j] == 1) {
                q.push({m - 1, j});
                grid[m - 1][j] = 0;
            }
        }
        
        // Directions: up, down, left, right
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // BFS from all boundary land cells
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (auto& d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                    grid[nx][ny] = 0;   // mark as visited (water)
                    q.push({nx, ny});
                }
            }
        }
        
        // Count remaining land cells (enclaves)
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) ++count;
            }
        }
        return count;
    }
};
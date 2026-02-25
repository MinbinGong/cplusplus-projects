/**
 * 994. Rotting Oranges
 *
 * In a given grid, each cell can have one of three values:
 *
 * the value 0 representing an empty cell;
 * the value 1 representing a fresh orange;
 * the value 2 representing a rotten orange.
 *
 * Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.
 *
 * Example 1:
 *
 * Input: [[2,1,1],[1,1,0],[0,1,1]]
 * Output: 4
 *
 * Example 2:
 *
 * Input: [[2,1,1],[0,1,1],[1,0,1]]
 * Output: -1
 *
 * Example 3:
 *
 * Input: [[0,2]]
 * Output: 0
 *
 * Note:
 *
 * 1 <= grid.length <= 10
 * 1 <= grid[0].length <= 10
 * grid[i][j] is only 0, 1, or 2.
 */
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        int fresh = 0;
        
        // Initialize queue with all rotten oranges and count fresh oranges
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    fresh++;
                }
            }
        }
        
        // If no fresh oranges, return 0
        if (fresh == 0) return 0;
        
        int minutes = 0;
        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // BFS level by level
        while (!q.empty() && fresh > 0) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                auto [r, c] = q.front();
                q.pop();
                
                for (auto [dr, dc] : dirs) {
                    int nr = r + dr;
                    int nc = c + dc;
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2;  // rot it
                        q.push({nr, nc});
                        fresh--;
                    }
                }
            }
            minutes++;  // one minute passes
        }
        
        return fresh == 0 ? minutes : -1;
    }
};
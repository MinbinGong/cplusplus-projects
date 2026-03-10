/**
 * 1730. Shortest Path to Get Food
 * 
 * You are starving and you want to eat food as quickly as possible. You want to find the shortest path to arrive at any food cell.
 * You are given an m x n character matrix, grid, of these different types of cells:
 * '*' is your location. There is exactly one '*' cell.
 * '#' is a food cell. There may be multiple food cells.
 * 'O' is free space, and you can travel through these cells.
 * 'X' is an obstacle, and you cannot travel through these cells.
 * You can travel to any adjacent cell north, east, south, or west of your current location if there is not an obstacle.
 * Return the length of the shortest path for you to reach any food cell. If there is no path for you to reach food, return -1.
 * 
 * Constraints:
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 200
 * grid[row][col] is '*', 'X', 'O', or '#'.
 * The grid contains exactly one '*'.
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int getFood(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        // 找起点
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '*') {
                    q.push({i, j});
                    visited[i][j] = true;
                    break;
                }
            }
        }
        
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto [r, c] = q.front();
                q.pop();
                
                if (grid[r][c] == '#') {
                    return steps;
                }
                
                for (auto& d : dirs) {
                    int nr = r + d[0];
                    int nc = c + d[1];
                    
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                        !visited[nr][nc] && grid[nr][nc] != 'X') {
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
            ++steps;
        }
        
        return -1;
    }
};
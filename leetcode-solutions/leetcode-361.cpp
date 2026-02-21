/*
 * 361. Bomb Enemy
 *
 * Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
 * The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
 * 
 * Note: You can only put the bomb at an empty cell.
 * 
 * Example:
 * Input: [["0","E","0","0"],["E","0","W","E"],["0","E","0","0"]]
 * Output: 3 
 * Explanation: For the given grid,
 * 
 * 0 E 0 0 
 * E 0 W E 
 * 0 E 0 0
 * 
 * Placing a bomb at (1,1) kills 3 enemies.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        
        // dp[i][j] 表示从四个方向能炸到的敌人数，这里我们分两个方向累积
        vector<vector<int>> up(m, vector<int>(n, 0));
        vector<vector<int>> down(m, vector<int>(n, 0));
        vector<vector<int>> left(m, vector<int>(n, 0));
        vector<vector<int>> right(m, vector<int>(n, 0));
        
        // 计算左边和上边的累积
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'W') {
                    left[i][j] = 0;
                    up[i][j] = 0;
                } else {
                    int enemy = (grid[i][j] == 'E') ? 1 : 0;
                    left[i][j] = (j > 0 ? left[i][j-1] : 0) + enemy;
                    up[i][j] = (i > 0 ? up[i-1][j] : 0) + enemy;
                }
            }
        }
        
        // 计算右边和下边的累积
        for (int i = m-1; i >= 0; --i) {
            for (int j = n-1; j >= 0; --j) {
                if (grid[i][j] == 'W') {
                    right[i][j] = 0;
                    down[i][j] = 0;
                } else {
                    int enemy = (grid[i][j] == 'E') ? 1 : 0;
                    right[i][j] = (j < n-1 ? right[i][j+1] : 0) + enemy;
                    down[i][j] = (i < m-1 ? down[i+1][j] : 0) + enemy;
                }
            }
        }
        
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '0') {
                    int total = left[i][j] + right[i][j] + up[i][j] + down[i][j];
                    ans = max(ans, total);
                }
            }
        }
        return ans;
    }
};
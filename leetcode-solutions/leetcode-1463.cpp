/**
 * 1463. Cherry Pickup II
 * 
 * Given a rows x cols matrix grid representing a field of cherries. Each cell in grid represents the number of cherries that you can collect.
 * 
 * You have two robots that can collect cherries for you, Robot #1 is located at the top-left corner (0,0) , and Robot #2 is located at the top-right corner (0, cols-1) of the grid.
 * 
 * Return the maximum number of cherries collection using both robots  by following the rules below:
 * 
 * From a cell (i,j), robots can move to cell (i+1, j-1) , (i+1, j) or (i+1, j+1).
 * When any robot is passing through a cell, It picks it up all cherries, and the cell becomes an empty cell (0).
 * When both robots stay on the same cell, only one of them takes the cherries.
 * Both robots cannot move outside of the grid at any moment.
 * Both robots should reach the bottom row in the grid.
 * 
 * Example 1:
 * 
 * Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
 * Output: 24
 * Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
 * Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
 * Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
 * Total of cherries: 12 + 12 = 24.
 * 
 * Example 2:
 * 
 * Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
 * Output: 28
 * Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
 * 
 * Note:
 * rows == grid.length
 * cols == grid[i].length
 * 2 <= rows, cols <= 70
 * 0 <= grid[i][j] <= 100 
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // dp[c1][c2] = maximum cherries collected up to current row with robot1 at c1, robot2 at c2
        vector<vector<int>> dp(cols, vector<int>(cols, -1));
        // initial positions at row 0
        dp[0][cols - 1] = grid[0][0] + grid[0][cols - 1]; // they start at different columns

        for (int r = 1; r < rows; ++r) {
            vector<vector<int>> new_dp(cols, vector<int>(cols, -1));

            for (int c1 = 0; c1 < cols; ++c1) {
                for (int c2 = 0; c2 < cols; ++c2) {
                    if (dp[c1][c2] == -1) continue; // unreachable state

                    // for each possible move of robot1 and robot2 (9 combinations)
                    for (int d1 = -1; d1 <= 1; ++d1) {
                        for (int d2 = -1; d2 <= 1; ++d2) {
                            int nc1 = c1 + d1;
                            int nc2 = c2 + d2;

                            if (nc1 < 0 || nc1 >= cols || nc2 < 0 || nc2 >= cols)
                                continue;

                            int cherries = grid[r][nc1] + (nc1 == nc2 ? 0 : grid[r][nc2]);
                            int total = dp[c1][c2] + cherries;

                            new_dp[nc1][nc2] = max(new_dp[nc1][nc2], total);
                        }
                    }
                }
            }
            dp = move(new_dp);
        }

        // answer is maximum over all final positions at last row
        int ans = 0;
        for (int c1 = 0; c1 < cols; ++c1)
            for (int c2 = 0; c2 < cols; ++c2)
                ans = max(ans, dp[c1][c2]);

        return ans;
    }
};
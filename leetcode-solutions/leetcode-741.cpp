/*
 * Cherry Pickup
 *
 * In a N x N grid representing a field of cherries, each cell is one of three possible integers.
 * 
 * 0 means the cell is empty, so you can pass through;
 * 1 means the cell contains a cherry, that you can pick up and pass through;
 * -1 means the cell contains a thorn that blocks your way.
 * 
 * Your task is to collect maximum number of cherries possible by following the rules below:
 * 
 * Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or down through valid path cells (cells with value 0 or 1);
 * After reaching (N-1, N-1), returning to (0, 0) by moving left or up through valid path cells;
 * When passing through a path cell containing a cherry, you pick it up and the cell becomes an empty cell (0);
 * If there is no valid path between (0, 0) and (N-1, N-1), then no cherries can be collected.
 * 
 * Note:
 * 1. N is the same for both rows and columns of grid.
 * 2. 1 <= N <= 50
 * 3. grid[i][j] is -1, 0, or 1.
 * 4. The starting point and the destination point are empty, i.e. grid[0][0] and grid[N-1][N-1] are 0.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        // dp[step][r1][r2] = max cherries collected after 'step' moves, with person1 at (r1, c1) and person2 at (r2, c2)
        // where c1 = step - r1, c2 = step - r2, and step = r1 + c1 = r2 + c2.
        // Since step ranges from 0 to 2n-2, and r1, r2 from 0 to n-1.
        // We use -1 to denote unreachable state.
        vector<vector<vector<int>>> dp(2 * n - 1, 
                                       vector<vector<int>>(n, 
                                       vector<int>(n, -1)));
        
        // Initial state: both at (0,0), step = 0
        dp[0][0][0] = grid[0][0]; // if grid[0][0] is -1, it will be -1 anyway
        
        for (int step = 1; step < 2 * n - 1; ++step) {
            for (int r1 = 0; r1 < n; ++r1) {
                int c1 = step - r1;
                if (c1 < 0 || c1 >= n) continue; // out of bounds
                if (grid[r1][c1] == -1) continue; // thorn
                
                for (int r2 = 0; r2 < n; ++r2) {
                    int c2 = step - r2;
                    if (c2 < 0 || c2 >= n) continue;
                    if (grid[r2][c2] == -1) continue;
                    
                    // previous step (step-1) we had possible moves: each person could come from up or left
                    // so four combinations: (r1-1,c1) or (r1,c1-1) for p1, similarly for p2
                    int best = -1;
                    // try all four possibilities
                    for (int dr1 = 0; dr1 <= 1; ++dr1) {
                        for (int dr2 = 0; dr2 <= 1; ++dr2) {
                            int prev_r1 = r1 - dr1;    // dr1=0 means from left? Actually careful:
                            // For person1: previous could be (r1-1, c1) if moving down (increase row) or (r1, c1-1) if moving right.
                            // At step-1, the row could be r1 (if moved right) or r1-1 (if moved down). So we need to consider r1 and r1-1 for p1.
                            // Similarly for p2.
                            // But we have two dimensions: we need to consider all combos: (r1, r2), (r1, r2-1), (r1-1, r2), (r1-1, r2-1)
                            // However we must ensure that previous step indices are valid.
                            // We'll use loops over delta: d1 in {0,1} meaning whether we came from up (d1=1 means previous row = r1-1) or left (d1=0 means previous row = r1)
                            // Actually we need to handle correctly: At step-1, row for p1 could be r1 (if moved from left, meaning previous col = c1-1) or r1-1 (if moved from up, previous col = c1). So previous row can be r1 or r1-1.
                            // So we can iterate over dr1 in {0,1} where dr1=1 means came from up (prev row = r1-1), dr1=0 means came from left (prev row = r1). But then we need to ensure that prev row is within [0,n-1] and prev col = step-1 - prev row is also valid.
                            // Similarly for p2.
                            int prev_r1 = r1 - dr1; // if dr1=1, prev_r1 = r1-1; if dr1=0, prev_r1 = r1
                            int prev_r2 = r2 - dr2;
                            if (prev_r1 < 0 || prev_r2 < 0) continue; // rows must be non-negative
                            int prev_c1 = (step - 1) - prev_r1;
                            int prev_c2 = (step - 1) - prev_r2;
                            if (prev_c1 < 0 || prev_c1 >= n || prev_c2 < 0 || prev_c2 >= n) continue;
                            if (dp[step-1][prev_r1][prev_r2] == -1) continue; // unreachable
                            
                            // valid previous state
                            best = max(best, dp[step-1][prev_r1][prev_r2]);
                        }
                    }
                    if (best == -1) continue; // no valid previous
                    
                    // Add current cherries: if both at same cell, add only once
                    int cur = best;
                    if (r1 == r2 && c1 == c2) {
                        cur += grid[r1][c1];
                    } else {
                        cur += grid[r1][c1] + grid[r2][c2];
                    }
                    dp[step][r1][r2] = cur;
                }
            }
        }
        
        int ans = dp[2*n-2][n-1][n-1];
        return max(ans, 0);
    }
};
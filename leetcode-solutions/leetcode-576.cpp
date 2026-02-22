/*
 * Out of Boundary Paths
 *
 * There is an m by n grid with a ball. Given the start coordinate (i,j) of the ball, you can move the ball to adjacent cell or cross the grid boundary in four directions (up, down, left, right).
 * However, you can at most move N times. Find out the number of paths to move the ball out of grid boundary. The answer may be very large, return it after mod 109 + 7.
 * 
 * Example:
 * Input: m = 2, n = 2, N = 2, i = 0, j = 0
 * Output: 6
 * 
 * Input: m = 1, n = 3, N = 3, i = 0, j = 1
 * Output: 12
 * 
 * Note:
 * Once you move the ball out of boundary, you cannot move it back.
 * The length and height of the grid is in range [1,50].
 * N is in range [0,50].
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        const int MOD = 1e9 + 7;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[startRow][startColumn] = 1;
        int ans = 0;
        int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        for (int move = 0; move < maxMove; ++move) {
            vector<vector<int>> newdp(m, vector<int>(n, 0));
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dp[i][j] == 0) continue;
                    for (auto& d : dirs) {
                        int ni = i + d[0], nj = j + d[1];
                        if (ni < 0 || ni >= m || nj < 0 || nj >= n) {
                            ans = (ans + dp[i][j]) % MOD;
                        } else {
                            newdp[ni][nj] = (newdp[ni][nj] + dp[i][j]) % MOD;
                        }
                    }
                }
            }
            dp = move(newdp);
        }
        return ans;
    }
};
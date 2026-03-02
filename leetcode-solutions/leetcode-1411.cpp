/**
 * 1411. Number of Ways to Paint N × 3 Grid
 * 
 * You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colours: Red, Yellow or Green while making sure that no two adjacent cells have the same colour (i.e no two cells that share vertical or horizontal sides have the same colour).
 * You are given n the number of rows of the grid.
 * Return the number of ways you can paint this grid. As the answer may grow large, the answer must be computed modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: n = 1
 * Output: 12
 * Explanation: There are 12 possible way to paint the grid as shown.
 * 
 * Example 2:
 * Input: n = 2
 * Output: 54
 * 
 * Example 3:
 * Input: n = 3
 * Output: 246
 * 
 * Example 4:
 * Input: n = 7
 * Output: 106494
 * 
 * Example 5:
 * Input: n = 5000
 * Output: 30228214
 * 
 * Note:
 * n == grid.length
 * grid[i].length == 3
 * 1 <= n <= 5000
 * 
 */
class Solution {
public:
    int numOfWays(int n) {
        const long long MOD = 1e9 + 7;
        // dp0: number of ways for current row ending with pattern ABA (first and last same)
        // dp1: number of ways ending with pattern ABC (all three distinct)
        long long dp0 = 6, dp1 = 6; // for n = 1
        for (int i = 2; i <= n; ++i) {
            long long new0 = (dp0 * 3 + dp1 * 2) % MOD;
            long long new1 = (dp0 * 2 + dp1 * 2) % MOD;
            dp0 = new0;
            dp1 = new1;
        }
        return (dp0 + dp1) % MOD;
    }
};
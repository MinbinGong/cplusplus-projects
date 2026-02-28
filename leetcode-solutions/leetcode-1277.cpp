/**
 * 1277. Count Square Submatrices with All Ones
 * 
 * Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.
 * 
 * Example 1:
 * Input: matrix =
 * [
 *   [0,1,1,1],
 *   [1,1,1,1],
 *   [0,1,1,1]
 * ]
 * Output: 15
 * Explanation: 
 * There are 10 squares of side 1.
 * There are 4 squares of side 2.
 * There is  1 square of side 3.
 * Total number of squares = 10 + 4 + 1 = 15.
 * 
 * Example 2:
 * Input: matrix = 
 * [
 *   [1,0,1],
 *   [1,1,0],
 *   [1,1,0]
 * ]
 * Output: 7
 * Explanation: 
 * There are 6 squares of side 1.  
 * 
 * Note:
 * 1 <= arrLen <= 10^6
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int total = 0;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 1) {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1; // 边界上只能形成边长为1的正方形
                    } else {
                        dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                    }
                    total += dp[i][j]; // 以(i,j)为右下角的所有边长正方形个数
                }
            }
        }
        return total;
    }
};
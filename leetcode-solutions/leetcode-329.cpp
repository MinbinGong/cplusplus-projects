/*
 * Longest Increasing Path in a Matrix
 * 
 * Given an m x n integers matrix, return the length of the longest increasing path in matrix.
 * 
 * From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
 * 
 * Example 1:
 * Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
 * Output: 4
 * Explanation: The longest increasing path is [1, 2, 6, 9].
 * 
 * Example 2:
 * Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
 * Output: 4
 * Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
 * 
 * Example 3:
 * Input: matrix = [[1]]
 * Output: 1
 * 
 */
#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>
using namespace std;

// int dfs(vector<vector<int>> &grey, vector<vector<int>> &memo, int i, int j, vector<vector<int>> &matrix) {
//   if (memo[i][j] != -1) return memo[i][j];

//   grey[i][j] = 1;

//   int maxNum{0};
//   if (i + 1 < matrix.size() && grey[i + 1][j] == 0 && matrix[i][j] < matrix[i + 1][j])
//     maxNum = max(maxNum, 1 + dfs(grey, memo, i + 1, j, matrix));
//   if (i > 0 && grey[i - 1][j] == 0 && matrix[i][j] < matrix[i - 1][j])
//     maxNum = max(maxNum, 1 + dfs(grey, memo, i - 1, j, matrix));
//   if (j + 1 < matrix[0].size() && grey[i][j + 1] == 0 && matrix[i][j] < matrix[i][j + 1])
//     maxNum = max(maxNum, 1 + dfs(grey, memo, i, j + 1, matrix));
//   if (j > 0 && grey[i][j - 1] == 0 && matrix[i][j] < matrix[i][j - 1])
//     maxNum = max(maxNum, 1 + dfs(grey, memo, i, j - 1, matrix));

//   grey[i][j] = 0;
//   return memo[i][j] = maxNum;
// }

// int longestIncreasingPath(vector<vector<int>> &matrix) {
//   int n = matrix.size();
//   if (n == 0) return 0;
//   int m = matrix[0].size();
//   if (m == 0) return 0;
//   int ret = 0;
//   vector<vector<int>> grey(n, vector<int>(m, 0));
//   vector<vector<int>> memo(n, vector<int>(m, -1));
//   for (size_t i = 0; i < n; i++) {
//     for (size_t j = 0; j < m; j++) {
//       ret = max(ret, dfs(grey, memo, i, j, matrix));
//     }
//   }
//   return ret;
// }

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> memo(m, vector<int>(n, 0));
        int ans = 0;
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        function<int(int, int)> dfs = [&](int x, int y) -> int {
            if (memo[x][y] != 0) return memo[x][y];
            int maxLen = 1; // 至少包含自身
            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && matrix[nx][ny] > matrix[x][y]) {
                    maxLen = max(maxLen, 1 + dfs(nx, ny));
                }
            }
            memo[x][y] = maxLen;
            return maxLen;
        };
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                ans = max(ans, dfs(i, j));
            }
        }
        return ans;
    }
};
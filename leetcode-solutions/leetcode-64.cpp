/*
    题目描述
        给定一个 m × n 大小的非负整数矩阵，求从左上角开始到右下角结束的、经过的数字的和最
    小的路径。每次只能向右或者向下移动
    题解
        我们可以定义一个同样是二维的 dp 数组，其中 dp[i][j] 表示从左上角开始到 (i, j) 位置的最
    优路径的数字和。因为每次只能向下或者向右移动，我们可以很容易得到状态转移方程 dp[i][j] =
    min(dp[i-1][j], dp[i][j-1]) + grid[i][j]，其中 grid 表示原数组。
 */
#include <vector>
using namespace std;

int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = grid[i][j];
            } else if (i == 0) {
                dp[i][j] = dp[i][j - 1] + grid[i][j];
            } else if (j == 0) {
                dp[i][j] = dp[i - 1][j] + grid[i][j];
            } else {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
    }
    return dp[m - 1][n - 1];
}

int minPathSum1(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<int> dp(n, 0);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) {
                dp[j] = grid[i][j];
            } else if (i == 0) {
                dp[j] = dp[j - 1] + grid[i][j];
            } else if (j == 0) {
                dp[j] = dp[j] + grid[i][j];
            } else {
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
            }
        }
    }
    return dp[n - 1];
}
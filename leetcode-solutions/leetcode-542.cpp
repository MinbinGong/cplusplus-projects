/*
    题目描述
    给定一个由 0 和 1 组成的二维矩阵，求每个位置到最近的 0 的距离

    题解
    一般来说，因为这道题涉及到四个方向上的最近搜索，所以很多人的第一反应可能会是广度
    优先搜索。但是对于一个大小 O„mn” 的二维数组，对每个位置进行四向搜索，最坏情况的时间复
    杂度（即全是 1）会达到恐怖的 O„m2n2”。一种办法是使用一个 dp 数组做 memoization，使得广
    度优先搜索不会重复遍历相同位置；另一种更简单的方法是，我们从左上到右下进行一次动态搜
    索，再从右下到左上进行一次动态搜索。两次动态搜索即可完成四个方向上的查找。
 */
#include <climits>
#include <vector>
using namespace std;

vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
    if (matrix.empty()) {
        return {};
    }
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX - 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 0) {
                dp[i][j] = 0;
            } else {
                if (j > 0) {
                    dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                }
                if (i > 0) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                }
            }
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (matrix[i][j] != 0) {
                if (j < m - 1) {
                    dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
                }
                if (i < n - 1) {
                    dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                }
            }
        }
    }
    return dp;
}
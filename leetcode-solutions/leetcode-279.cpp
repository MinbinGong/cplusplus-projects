/*
    Perfect squares

    题目描述
        给定一个正整数，求其最少可以由几个完全平方数相加构成。

    题解
        对于分割类型题，动态规划的状态转移方程通常并不依赖相邻的位置，而是依赖于满足分割
    条件的位置。我们定义一个一维矩阵 dp，其中 dp[i] 表示数字 i 最少可以由几个完全平方数相加
    构成。在本题中，位置 i 只依赖 i - k 2 的位置，如 i - 1、i - 4、i - 9 等等，才能满足完全平方分割
    的条件。因此 dp[i] 可以取的最小值即为 1 + min(dp[i-1], dp[i-4], dp[i-9] · · · )。
 */

#include <algorithm>
#include <vector>
int numSquares(int n) {
  std::vector<int> dp(n + 1, n);
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j * j <= i; ++j) {
      dp[i] = std::min(dp[i], dp[i - j * j] + 1);
    }
  }
  return dp[n]
}
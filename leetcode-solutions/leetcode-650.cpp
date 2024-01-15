/*
Keys Keyboard

题目描述
给定一个字母 A，已知你可以每次选择复制全部字符，或者粘贴之前复制的字符，求最少需
要几次操作可以把字符串延展到指定长度

题解
不同于以往通过加减实现的动态规划，这里需要乘除法来计算位置，因为粘贴操作是倍数增
加的。我们使用一个一维数组 dp，其中位置 i 表示延展到长度 i 的最少操作次数。对于每个位置
j，如果 j 可以被 i 整除，那么长度 i 就可以由长度 j 操作得到，其操作次数等价于把一个长度为 1
的 A 延展到长度为 i/j。因此我们可以得到递推公式 dp[i] = dp[j] + dp[i/j]。
*/
#include <cmath>
#include <vector>
using namespace std;

int minSteps(int n) {
  vector<int> dp(n + 1);
  int h = sqrt(n);
  for (int i = 2; i <= n; ++i) {
    dp[i] = i;
    for (int j = 2; j <= h; ++j) {
      if (i % j == 0) {
        dp[i] = dp[j] + dp[i / j];
        break;
      }
    }
  }
  return dp[n];
}
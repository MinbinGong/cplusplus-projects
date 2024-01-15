/*
Coin Change

题目描述
给定一些硬币的面额，求最少可以用多少颗硬币组成给定的金额。

题解
因为每个硬币可以用无限多次，这道题本质上是完全背包。我们直接展示二维空间压缩为一
维的写法。
这里注意，我们把 dp 数组初始化为 amount + 2 而不是-1 的原因是，在动态规划过程中有求
最小值的操作，如果初始化成-1 则会导致结果始终为-1。至于为什么取这个值，是因为 i 最大可
以取 amount + 1，而最多的组成方式是只用 1 元硬币，因此 amount + 2 一定大于所有可能的组合
方式，取最小值时一定不会是它。在动态规划完成后，若结果仍然是此值，则说明不存在满足条
件的组合方法，返回-1。
 */
#include <vector>
using namespace std;

int coinChange(vector<int>& coins, int amount) {
  if (coins.empty()) {
    return -1;
  }

  vector<int> dp(amount + 1, amount + 2);
  dp[0] = 0;
  for (int i = 1; i <= amount; ++i) {
    for (const int& coin : coins) {
      if (i >= coin) {
        dp[i] = min(dp[i], dp[i - coin] + 1);
      }
    }
  }

  return dp[amount] == amount + 2 ? -1 : dp[amount];
}
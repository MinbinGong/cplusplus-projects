/*
Best time to buy and sell stock with cooldown

题目描述
给定一段时间内每天的股票价格，已知每次卖出之后必须冷却一天，且每次只能拥有一支股
票，求最大的收益。

题解
我们可以使用状态机来解决这类复杂的状态转移问题，通过建立多个状态以及它们的转移方
式，我们可以很容易地推导出各个状态的转移方程。如图所示，我们可以建立四个状态来表示带
有冷却的股票交易，以及它们的之间的转移方式。
 */
#include <algorithm>
#include <vector>
using namespace std;

int maxProfit(vector<int>& prices) {
  int n = prices.size();
  if (n <= 1) return 0;

  int buy{0}, sell{1};
  int dp[3][2];

  for (int i = 1; i < n; i++) {
    dp[2][sell] = max(dp[1][sell], dp[1][buy] + prices[i]);
    dp[2][buy] = -prices[i];

    if (i >= 2) {
      dp[2][buy] += dp[0][sell];
    }
    dp[2][buy] = max(dp[2][buy], dp[1][buy]);

    for (int k = 0; k < 2; k++) {
      dp[0][k] = dp[1][k];
      dp[1][k] = dp[2][k];
    }
  }

  return dp[2][sell];
}

int maxProfit1(vector<int>& prices) {
  int n = prices.size();
  if (n == 0) {
    return 0;
  }

  vector<int> buy(n), sell(n), s1(n), s2(n);
  s1[0] = buy[0] = -prices[0];
  sell[0] = s2[0] = 0;

  for (int i = 0; i < n; ++i) {
    buy[i] = s2[i - 1] - prices[i];
    s1[i] = max(buy[i - 1], s1[i - 1]);
    sell[i] = max(buy[i - 1], s1[i - 1]) + prices[i];
    s2[i] = max(s2[i - 1], sell[i - 1]);
  }
  return max(sell[n - 1], s2[n - 1]);
}
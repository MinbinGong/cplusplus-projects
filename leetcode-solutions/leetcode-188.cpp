/*
Best Time to Buy and Sell Stock

题目描述
给定一段时间内每天的股票价格，已知你只可以买卖各 k 次，且每次只能拥有一支股票，求
最大的收益。

题解
如果 k 大约总天数，那么我们一旦发现可以赚钱就进行买卖。如果 k 小于总天数，我们可以
建立两个动态规划数组 buy 和 sell，对于每天的股票价格，buy[j] 表示在第 j 次买入时的最大收
益，sell[j] 表示在第 j 次卖出时的最大收益。
 */
#include <climits>
#include <vector>
using namespace std;

int maxProfitUnlimited(vector<int>& prices) {
  int maxProfit = 0;
  for (int i = 1; i < prices.size(); ++i) {
    if (prices[i] > prices[i - 1]) {
      maxProfit += prices[i] - prices[i - 1];
    }
  }
  return maxProfit;
}

int maxProfit(int k, vector<int>& prices) {
  int days = prices.size();
  if (days < 2) {
    return 0;
  }

  if (k >= days) {
    return maxProfitUnlimited(prices);
  }

  vector<int> buy(k + 1, INT_MIN), sell(k + 1, 0);
  for (int i = 0; i < days; ++i) {
    for (int j = 0; j <= k; ++j) {
      buy[j] = max(buy[j], sell[j - 1] - prices[i]);
      sell[j] = max(sell[j], buy[j] + prices);
    }
  }
  return sell[k];
}
/*
 * Best time to buy and sell stock with cooldown
 *
 * Given a list of daily prices of a stock, design an algorithm to find the maximum profit. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:
 * 
 * You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).
 * After you sell your stock, you cannot buy stock on the next day. (i.e., cooldown 1 day)
 * 
 * Example 1:
 * Input: [1,2,3,0,2]
 * Output: 3 
 * Explanation: transactions = [buy, sell, cooldown, buy, sell]
 * 
 * Example 2:
 * Input: [1]
 * Output: 0
 * 
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
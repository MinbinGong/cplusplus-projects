/*
  Best Time to Buy and Sell Stock III

  You are given an array prices where prices[i] is the price of a given stock on the ith day.

  Find the maximum profit you can achieve. You may complete at most two transactions.

  Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 */
#include <climits>
#include <vector>
using namespace std;

int maxProfit(vector<int>& prices) {
  if (prices.empty()) {
    return 0;
  }

  int lowPrice = INT_MAX;
  int maxProfit = INT_MIN;
  int transitionalProfit = INT_MIN;
  int finalProfit = INT_MIN;
  for (int p : prices) {
    lowPrice = min(lowPrice, p);
    maxProfit = max(maxProfit, p - lowPrice);

    transitionalProfit = max(transitionalProfit, maxProfit - p);
    finalProfit = max(finalProfit, transitionalProfit + p);
  }

  return finalProfit;
}
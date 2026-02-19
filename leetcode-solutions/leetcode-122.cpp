/*
 * Best Time to Buy and Sell Stock II
 *
 * You are given an integer array prices where prices[i] is the price of a given stock on the ith day.
 * You want to maximize your profit by choosing a single day to buy one stock 
 * and choosing a different day in the future to sell that stock.
 * 
 * On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any
 * time. However, you can buy it then immediately sell it on the same day.
 * 
 * Find and return the maximum profit you can achieve.
 */
#include <vector>
using namespace std;

int maxProfit(vector<int>& prices) {
  int j = prices.size() - 1, i = j - 1, res = 0;
  while (i >= 0) {
    if (prices[j] - prices[i] > 0) {
      res += prices[j] - prices[i];
      j--;
    } else {
      j = i;
    }
    i--;
  }
  return res;
}
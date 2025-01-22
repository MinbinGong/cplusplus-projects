/*
 * @lc app=leetcode.cn id=583 lang=cpp
 * Best Time to Buy and Sell Stock with Transaction Fee
 * You are given an array prices where prices[i] is the price of a given stock on the ith day,
 * and an integer fee representing a transaction fee.
 * 
 * Find the maximum profit you can achieve.
 * You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.
 * 
 * Note:
 * 1. You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
 * 2. The transaction fee is only charged once for each stock purchase and sale.
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<int> dp(n, 0);
        int minPrice = prices[0];
        for (int i = 1; i < n; i++) {
            dp[i] = max(dp[i - 1], prices[i] - minPrice - fee);
            minPrice = min(minPrice, prices[i] - dp[i]);
        }
        return dp[n - 1];
    }
};
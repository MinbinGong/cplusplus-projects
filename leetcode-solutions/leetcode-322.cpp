/*
 * Coin Change
 *
 * Given an array of coin denominations and a total amount, find the minimum number of coins required to make up that amount.
 * If it is not possible to make up the amount with the given coins, return -1.
 * 
 * Example 1:
 * Input: coins = [1, 2, 5], amount = 11
 * Output: 3
 * Explanation: 11 = 5 + 5 + 1
 * 
 * Example 2:
 * Input: coins = [2], amount = 3
 * Output: -1
 * 
 * Example 3:
 * Input: coins = [1], amount = 0
 * Output: 0
 * 
 * Example 4:
 * Input: coins = [1], amount = 1
 * Output: 1
 * 
 * Example 5:
 * Input: coins = [1], amount = 2
 * Output: 2
 * 
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
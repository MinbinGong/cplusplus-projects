/*
 * Can I Win
 *
 * In the "100 game" two players take turns adding, to a running total, any integer from 1 to 10. The player who first causes the running total to reach or exceed 100 wins.
 *
 * What if we change the game so that players cannot re-use integers?
 *
 * For example, two players might take turns drawing from a common pool of numbers from 1 to 15 without replacement until they reach a total >= 100.
 *
 * Given two integers maxChoosableInteger and desiredTotal, return true if the first player to move can force a win, otherwise, return false. Assume both players play optimally.
 *
 * Constraints:
 * 1 <= maxChoosableInteger <= 20
 * 0 <= desiredTotal <= 300
 * 
 */
#include <functional>
#include <unordered_map>
using namespace std;

bool canIWin(int maxChoosableInteger, int desiredTotal) {
  if (desiredTotal <= 0) return true;

  const int sum = maxChoosableInteger * (maxChoosableInteger + 1) / 2;
  if (sum < desiredTotal) return false;

  unordered_map<int, bool> memo;  // true: can win, false: can't win

  // state: record integers that have been chosen
  function<bool(int, int)> dp = [&](int total, int state) {
    if (total <= 0) return false;
    if (memo.count(state)) return memo[state];

    for (int i = 1; i <= maxChoosableInteger; ++i) {
      if (state & (1 << i)) continue;  // integer i is used
      if (!dp(total - i, state | (1 << i))) return true;
    }

    return memo[state] = false;
  };

  return dp(desiredTotal, 0);
}
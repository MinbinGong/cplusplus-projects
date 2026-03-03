/**
 * 1510. Stone Game IV
 * 
 * Alice and Bob take turns playing a game, with Alice starting first.
 * Initially, there are n stones in a pile. On each player's turn, that player makes a move consisting of removing any non-zero square number of stones in the pile.
 * Also, if a player cannot make a move, he/she loses the game.
 * Given a positive integer n, return true if and only if Alice wins the game otherwise return false, assuming both players play optimally.
 * 
 * Example 1:
 * Input: n = 1
 * Output: true
 * Explanation: Alice can remove 1 stone winning the game because Bob doesn't have any moves.
 * 
 * Example 2:
 * Input: n = 2
 * Output: false
 * Explanation: Alice can only remove 1 stone, after that Bob removes the last one winning the game (2 -> 1 -> 0).
 * 
 * Example 3:
 * Input: n = 4
 * Output: true
 * Explanation: Alice can remove 4 stones (2^2) winning the game because Bob doesn't have any moves.
 * 
 * Example 4:
 * Input: n = 7
 * Output: false
 * Explanation: Alice can't win the game if Bob plays optimally.
 * If Alice starts removing 4 stones, Bob will remove 1 stone then Alice should remove only 1 stone and finally Bob removes the last one (7 -> 3 -> 2 -> 1 -> 0). 
 * If Alice starts removing 1 stone, Bob will remove 4 stones then Alice only can remove 1 stone and finally Bob removes the last one (7 -> 6 -> 2 -> 1 -> 0).
 * 
 */
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    bool winnerSquareGame(int n) {
        // dp[i] 表示当剩余 i 个石子时，当前玩家（先手）是否能获胜
        vector<bool> dp(n + 1, false);
        
        for (int i = 1; i <= n; i++) {
            // 尝试所有可能的平方数
            for (int j = 1; j * j <= i; j++) {
                // 如果存在一种取法使得对手处于必败状态，则当前玩家获胜
                if (!dp[i - j * j]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[n];
    }
};
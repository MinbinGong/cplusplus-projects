/*
 * 1690. Stone Game VII
 *
 * Alice and Bob take turns playing a game, with Alice starting first.
 * 
 * There are n stones arranged in a row. On each player's turn, they can remove either the leftmost stone or the rightmost stone from the row and receive points equal to the sum of the remaining stones' values in the row. The winner is the one with the higher score when there are no stones left to remove.
 * 
 * Bob found that he will always lose this game (poor Bob, he always loses), so he decided to minimize the score's difference. Alice's goal is to maximize the difference in the score.
 * 
 * Given an array of integers stones where stones[i] represents the value of the ith stone from the left, return the difference in Alice and Bob's score if they both play optimally.
 * 
 * Example 1:
 * Input: stones = [5,3,1,4,2]
 * Output: 6
 * Explanation: 
 * - Alice removes 2 and gets 5 + 3 + 1 + 4 = 13 points. Alice = 13, Bob = 0, stones = [5,3,1,4].
 * 
 * Example 2:
 * Input: stones = [7,90,5,1,100,10,10,2]
 * Output: 122
 * Explanation: Details of the tournament:
 * - 1st Round: Teams = 8, Matches = 7, and 4 teams advance.
 * - 2nd Round: Teams = 4, Matches = 3, and 2 teams advance.
 * - 3rd Round: Teams = 2, Matches = 1, and 1 team is declared the winner.
 * Total number of matches = 7 + 3 + 1 = 11.
 * 
 * Constraints:
 * n == stones.length
 * 2 <= n <= 1000
 * 1 <= stones[i] <= 1000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        // prefix sums for O(1) range sum queries
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + stones[i];
        }
        auto sum = [&](int i, int j) {
            return prefix[j + 1] - prefix[i];
        };

        // dp[i][j] = best score difference current player can obtain on stones[i..j]
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // iterate by increasing length of subarray
        for (int length = 2; length <= n; ++length) {
            for (int i = 0; i + length <= n; ++i) {
                int j = i + length - 1;
                // option 1: take the left stone
                int leftScore = sum(i + 1, j) - dp[i + 1][j];
                // option 2: take the right stone
                int rightScore = sum(i, j - 1) - dp[i][j - 1];
                dp[i][j] = max(leftScore, rightScore);
            }
        }

        return dp[0][n - 1];
    }
};
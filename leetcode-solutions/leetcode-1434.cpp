/*
 * 1434. Number of Ways to Wear Different Hats to Each Other
 *
 * There are n people and 40 types of hats labeled from 1 to 40.
 * 
 * Given a list of list of integers hats, where hats[i] is a list of all hats preferred by the i-th person.
 * 
 * Return the number of ways that the n people wear different hats to each other.
 * 
 * Since the answer may be too large, return it modulo 10^9 + 7.
 * 
 * Example 1:
 * 
 * Input: hats = [[3,4],[4,5],[5]]
 * Output: 1
 * Explanation: There is only one way to choose hats given the conditions. 
 * First person choose hat 3, Second person choose hat 4 and last one hat 5.
 * 
 * Example 2:
 * 
 * Input: hats = [[3,5,1],[3,5]]
 * Output: 4
 * Explanation: There are 4 ways to choose hats (3,5,1), (3,5), (5,1), (3,1)
 * 
 * Example 3:
 * 
 * Input: hats = [[1,2,3,4],[1,2,3,4],[1,2,3,4],[1,2,3,4]]
 * Output: 24
 * Explanation: Each person can choose hats labeled from 1 to 4.
 * Number of Permutations of (1,2,3,4) = 24.
 * 
 * Example 4:
 * 
 * Input: hats = [[1,2,3],[2,3,5,6],[1,3,7,9],[1,8,9],[2,5,7]]
 * Output: 111
 * Explanation: There are 111 ways to choose hats.
 * 
 * Note:
 * n == hats.length
 * 1 <= n <= 10
 * 1 <= hats[i].length <= 40
 * 1 <= hats[i][j] <= 40
 * hats[i] contains a list of unique integers.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {
        const int MOD = 1e9 + 7;
        int n = hats.size();
        // hatToPeople[hat] = list of people who like this hat (hat numbered 1..40)
        vector<vector<int>> hatToPeople(41);
        for (int i = 0; i < n; ++i) {
            for (int h : hats[i]) {
                hatToPeople[h].push_back(i);
            }
        }

        vector<int> dp(1 << n, 0);
        dp[0] = 1;                               // no one has a hat yet

        for (int hat = 1; hat <= 40; ++hat) {
            vector<int> ndp = dp;                 // start with skipping this hat
            for (int mask = 0; mask < (1 << n); ++mask) {
                if (dp[mask] == 0) continue;     // no ways for this mask
                // try giving current hat to each person who likes it and is free
                for (int p : hatToPeople[hat]) {
                    if (!(mask & (1 << p))) {
                        int newMask = mask | (1 << p);
                        ndp[newMask] = (ndp[newMask] + dp[mask]) % MOD;
                    }
                }
            }
            dp = move(ndp);
        }

        return dp[(1 << n) - 1];                 // all people have a hat
    }
};

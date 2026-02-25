/**
 * 1000. Minimum Cost to Merge Stones
 *
 * There are N piles of stones arranged in a row.  The i-th pile has stones[i] stones.
 *
 * A move consists of merging exactly K consecutive piles into one pile, and the cost of this move is equal to the total number of stones in these K piles.
 *
 * Find the minimum cost to merge all piles of stones into one pile.  If it is impossible, return -1.
 *
 * Example 1:
 *
 * Input: stones = [3,2,4,1], K = 2
 * Output: 20
 * Explanation: 
 * We start with [3, 2, 4, 1].
 * We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
 * We merge [4, 1] for a cost of 5, and we are left with [5, 5].
 * We merge [5, 5] for a cost of 10, and we are left with [10].
 * 
 * Example 2:
 *
 * Input: stones = [3,2,4,1], K = 3
 * Output: -1
 * Explanation: After any merge move, there are 2 piles left, and we can't merge anymore.  So the task is impossible.
 * 
 * Example 3:
 *
 * Input: stones = [3,5,1,2,6], K = 3
 * Output: 25
 * Explanation: 
 * We start with [3, 5, 1, 2, 6].
 * We merge [5, 1, 2] for a cost of 8, and we are left with [3, 8, 6].
 * We merge [3, 8, 6] for a cost of 17, and we are left with [17].
 * 
 * Note:
 *
 * 1 <= stones.length <= 30
 * 2 <= K <= 30
 * 1 <= stones[i] <= 100
 */
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int mergeStones(vector<int>& stones, int K) {
        int n = stones.size();
        // If it's impossible to merge into one pile
        if ((n - 1) % (K - 1) != 0) return -1;

        // Prefix sums for quick range sum calculation
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i)
            prefix[i + 1] = prefix[i] + stones[i];

        // dp[i][j] = minimum cost to merge stones[i..j] into one pile
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Iterate over interval lengths (starting from K because smaller ones cannot be merged)
        for (int len = K; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;

                // Try all splits where the left part can be merged into one pile
                // i.e., (m - i) is a multiple of (K-1)
                for (int m = i; m < j; m += K - 1) {
                    dp[i][j] = min(dp[i][j], dp[i][m] + dp[m + 1][j]);
                }

                // If the whole interval can be merged into one pile,
                // add the cost of the final merge (total stones in the interval)
                if ((j - i) % (K - 1) == 0) {
                    dp[i][j] += prefix[j + 1] - prefix[i];
                }
            }
        }

        return dp[0][n - 1];
    }
};
/**
 * 1420. Build Array Where You Can Find The Maximum Exactly K Comparisons
 * 
 * Given three integers n, m and k. Consider the following algorithm to find the maximum element of an array of positive integers:
 * 
 * Example 1:
 * 
 * Input: n = 2, m = 3, k = 1
 * Output: 6
 * Explanation: 
 * Arrays = [1, 2], [1, 3], [2, 1], [2, 3], [3, 1], [3, 2]
 * Maximums of each array = 2, 3, 2, 3, 3, 2
 * Second maximum of each array = 1, 1, 2, 2, 2, 2
 * Number of times second maximum is 1 = 6
 * 
 * Example 2:
 * 
 * Input: n = 5, m = 2, k = 3
 * Output: 0
 * Explanation: The possible arrays are [1, 1, 1, 1, 1], [1, 1, 1, 1, 2], [1, 1, 1, 2, 2], [1, 1, 2, 2, 2], [1, 2, 2, 2, 2], [2, 2, 2, 2, 2].
 * 
 * Example 3:
 * 
 * Input: n = 3, m = 1, k = 2
 * Output: 0
 * Explanation: The possible array is [1, 1, 1].
 * 
 * Note:
 * 1 <= n <= 50
 * 1 <= m <= 100
 * 0 <= k <= n
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int numOfArrays(int n, int m, int k) {
        const int MOD = 1e9 + 7;
        // dp[i][j][c] = number of ways to fill first i elements,
        // with current maximum = j, and exactly c updates so far.
        vector<vector<vector<long long>>> dp(
            n + 1, vector<vector<long long>>(m + 1, vector<long long>(k + 1, 0)));

        // Base case: first element always causes an update.
        for (int j = 1; j <= m; ++j) {
            dp[1][j][1] = 1;
        }

        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= m; ++j) {
                for (int c = 0; c <= k; ++c) {
                    long long val = dp[i][j][c];
                    if (val == 0) continue;

                    // Next element ≤ current maximum → no new update.
                    // There are j choices (1 .. j) that keep max = j.
                    dp[i + 1][j][c] = (dp[i + 1][j][c] + val * j) % MOD;

                    // Next element > current maximum → new update.
                    // New maximum becomes x (j+1 .. m).
                    for (int x = j + 1; x <= m; ++x) {
                        if (c + 1 <= k) {
                            dp[i + 1][x][c + 1] = (dp[i + 1][x][c + 1] + val) % MOD;
                        }
                    }
                }
            }
        }

        long long ans = 0;
        for (int j = 1; j <= m; ++j) {
            ans = (ans + dp[n][j][k]) % MOD;
        }
        return ans;
    }
};
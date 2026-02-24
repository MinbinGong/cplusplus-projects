/*
 * Number of Music Playlists
 *
 * Your music player contains N different songs and she wants to listen to L (not necessarily different) songs during your trip.  You create a playlist so that:
 *
 * Every song is played at least once
 * A song can only be played again only if K other songs have been played
 * Return the number of possible playlists.  As the answer can be very large, return it modulo 10^9 + 7.
 *
 * Example 1:
 * Input: N = 3, L = 3, K = 1
 * Output: 6
 * Explanation: There are 6 possible playlists. [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1].
 *
 * Example 2:
 * Input: N = 2, L = 3, K = 0
 * Output: 6
 * Explanation: There are 6 possible playlists. [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 2, 1], [2, 1, 2], [1, 2, 2].
 * 
 * Example 3:
 * Input: N = 2, L = 3, K = 1
 * Output: 2
 * Explanation: There are 2 possible playlists. [1, 2, 1], [2, 1, 2].
 * 
 * Note:
 * 1 <= N <= 100
 * 1 <= L <= 100
 * 0 <= K <= N
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k) {
        const int MOD = 1e9 + 7;
        
        // dp[i][j] = number of playlists of length i with exactly j unique songs
        vector<vector<long long>> dp(goal + 1, vector<long long>(n + 1, 0));
        dp[0][0] = 1;  // empty playlist, 0 songs used
        
        for (int i = 1; i <= goal; ++i) {
            for (int j = 1; j <= n; ++j) {
                // Case 1: Add a new song (never played before)
                // We have (n - (j - 1)) choices for which new song to add
                dp[i][j] = (dp[i - 1][j - 1] * (n - j + 1)) % MOD;
                
                // Case 2: Repeat a song that has been played before
                // To avoid repeating within the last k songs, we have (j - k) choices
                if (j > k) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j] * (j - k)) % MOD;
                }
            }
        }
        
        return dp[goal][n];
    }
};
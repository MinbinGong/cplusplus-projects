/*
 * 1335. Minimum Difficulty of a Job Schedule
 *
 * You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the i-th job, you have to finish all the jobs j where 0 <= j < i).
 * 
 * You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job done in that day.
 * 
 * Example 1:
 * Input: jobDifficulty = [6,5,4,3,2,1], d = 2
 * Output: 7
 * Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
 * Second day you can finish the last job, total difficulty = 1.
 * The difficulty of the schedule = 6 + 1 = 7
 * 
 * Example 2:
 * Input: jobDifficulty = [9,9,9], d = 4
 * Output: -1
 * Explanation: If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.
 * 
 * Example 3:
 * Input: jobDifficulty = [1,1,1], d = 3
 * Output: 3
 * Explanation: The schedule is one job per day. total difficulty will be 3.
 * 
 * Example 4:
 * Input: jobDifficulty = [7,1,7,1,7,1], d = 3
 * Output: 15
 * Explanation: First day you can finish the first 3 jobs, total difficulty = 7.
 * Second day you can finish the next 2 jobs, total difficulty = 7.
 * Third day you can finish the last job, total difficulty = 1.
 * The difficulty of the schedule = 7 + 7 + 1 = 15
 * 
 * Note:
 * 1 <= jobDifficulty.length <= 300
 * 0 <= jobDifficulty[i] <= 1000
 * 1 <= d <= 10
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        // If there are more days than jobs, it's impossible to have non‑empty days.
        if (d > n) return -1;

        // Precompute the maximum difficulty for every subarray [i, j].
        vector<vector<int>> maxDiff(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            maxDiff[i][i] = jobDifficulty[i];
            for (int j = i + 1; j < n; ++j) {
                maxDiff[i][j] = max(maxDiff[i][j - 1], jobDifficulty[j]);
            }
        }

        const int INF = 1e9;
        // dp[i][k] = minimum total difficulty for the first i jobs (0..i-1) split into k days.
        vector<vector<int>> dp(n + 1, vector<int>(d + 1, INF));
        dp[0][0] = 0;   // zero jobs, zero days → zero difficulty

        for (int i = 1; i <= n; ++i) {               // i = number of jobs processed
            for (int k = 1; k <= d; ++k) {           // k = number of days used
                // The last day must cover jobs j ... i-1 (1‑based: j+1 ... i)
                // and j must be at least k-1 so that the first k-1 days can be non‑empty.
                for (int j = k - 1; j < i; ++j) {
                    dp[i][k] = min(dp[i][k],
                                   dp[j][k - 1] + maxDiff[j][i - 1]);
                }
            }
        }

        return dp[n][d];
    }
};
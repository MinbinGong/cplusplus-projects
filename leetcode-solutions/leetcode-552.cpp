/*
 * Student Attendance Record II
 *
 * You are given a string representing an attendance record for a student. The record only contains the following three characters:
 * 'A' : Absent.
 * 'L' : Late.
 * 'P' : Present.
 * A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).
 * 
 * You need to return whether the student could be rewarded according to his attendance record.
 * 
 * Example 1:
 * Input: "PPALLP"
 * Output: True
 * 
 * Example 2:
 * Input: "PPALLL"
 * Output: False
 * 
 * Note:
 * The length of the input string will be in range [1, 1000].
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int checkRecord(int n) {
        const int MOD = 1e9 + 7;
        // dp[a][l]: a = 0 or 1 (absences), l = 0,1,2 (consecutive lates at end)
        vector<vector<long>> dp(2, vector<long>(3, 0));
        dp[0][0] = 1; // empty sequence

        for (int i = 0; i < n; ++i) {
            vector<vector<long>> newdp(2, vector<long>(3, 0));
            for (int a = 0; a < 2; ++a) {
                for (int l = 0; l < 3; ++l) {
                    long cur = dp[a][l];
                    if (cur == 0) continue;
                    // Add 'P' (present)
                    newdp[a][0] = (newdp[a][0] + cur) % MOD;
                    // Add 'A' (absent) - only if no absence yet
                    if (a == 0) {
                        newdp[1][0] = (newdp[1][0] + cur) % MOD;
                    }
                    // Add 'L' (late) - only if less than 2 consecutive lates
                    if (l < 2) {
                        newdp[a][l + 1] = (newdp[a][l + 1] + cur) % MOD;
                    }
                }
            }
            dp = move(newdp);
        }

        long ans = 0;
        for (int a = 0; a < 2; ++a)
            for (int l = 0; l < 3; ++l)
                ans = (ans + dp[a][l]) % MOD;
        return ans;
    }
};
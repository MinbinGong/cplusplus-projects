/**
 * 1349. Maximum Number of Students Taking Exam
 * 
 * Given a m * n matrix seats that represent seats distributions in a classroom. If a seat is broken, it is denoted by '#' character otherwise it is denoted by a '.' character.
 * 
 * Students can see the answers of those sitting next to the left, right, upper left and upper right, but he cannot see the answers of the student sitting directly in front or behind him. Return the maximum number of students that can take the exam together without any cheating being possible.
 * 
 * Students must be placed in seats in good condition.
 * 
 * Example 1:
 * Input: seats = [["#",".","#","#",".","#"],
 *                 [".","#","#","#","#","."],
 *                 ["#",".","#","#",".","#"]]
 * Output: 4
 * Explanation: Teacher can place 4 students in available seats so they don't cheat on the exam. 
 * 
 * Example 2:
 * Input: seats = [[".","#"],
 *                 ["#","#"],
 *                 ["#","."],
 *                 ["#","#"]]
 * Output: 3
 * Explanation: Place all students in available seats. 
 * 
 * Example 3:
 * Input: seats = [["#",".",".",".","#"],
 *                 [".","#",".","#","."],
 *                 [".",".","#",".","."],
 *                 [".","#",".","#","."],
 *                 ["#",".",".",".","#"]]
 * Output: 10
 * Explanation: Place students in available seats in column 1, 3 and 5.
 * 
 * Note:
 * seats contains only characters '.' and'#'.
 * m == seats.length
 * n == seats[i].length
 * 1 <= m <= 8
 * 1 <= n <= 8
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size(), n = seats[0].size();
        vector<int> valid(m, 0);  // valid[i]: bitmask of available seats in row i

        // Step 1: Convert each row's available seats to a bitmask
        for (int i = 0; i < m; ++i) {
            int mask = 0;
            for (int j = 0; j < n; ++j) {
                if (seats[i][j] == '.') {
                    mask |= (1 << j);
                }
            }
            valid[i] = mask;
        }

        vector<vector<int>> dp(m + 1, vector<int>(1 << n, -1));
        dp[0][0] = 0;  // Base case: before first row, no students

        // Step 2: DP over rows
        for (int i = 0; i < m; ++i) {
            for (int prevMask = 0; prevMask < (1 << n); ++prevMask) {
                if (dp[i][prevMask] == -1) continue;  // unreachable state

                // Try all possible seat arrangements for current row
                for (int curMask = 0; curMask < (1 << n); ++curMask) {
                    // Check 1: Can only place students on available seats
                    if ((curMask & valid[i]) != curMask) continue;

                    // Check 2: No adjacent students in the same row
                    if (curMask & (curMask >> 1)) continue;

                    // Check 3: No diagonal conflicts with previous row
                    if ((prevMask & (curMask >> 1)) || (prevMask & (curMask << 1))) continue;

                    int students = __builtin_popcount(curMask);
                    dp[i + 1][curMask] = max(dp[i + 1][curMask], dp[i][prevMask] + students);
                }
            }
        }

        // Step 3: Find the maximum over all states in the last row
        int ans = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            ans = max(ans, dp[m][mask]);
        }
        return ans;
    }
};
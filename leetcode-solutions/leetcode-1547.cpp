/**
 * 1547. Minimum Cost to Cut a Stick
 * 
 * Given a wooden stick of length n units. The stick is labelled from 0 to n. For example, a stick of length 6 is labelled as follows:
 * 
 * 
 * Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.
 * 
 * You should perform the cuts in order, you can change the order of the cuts as you wish.
 * 
 * The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts. When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the stick before the cut). Please refer to the first example for a better explanation.
 * 
 * Return the minimum total cost of the cuts.
 * 
 * 
 * Example 1:
 * Input: n = 7, cuts = [1,3,4,5]
 * Output: 16
 * Explanation: The cuts are shown in the figure above.
 * The first cut is done to a rod of length 7 so the cost is 7. The second cut is done to a rod of length 6 (i.e. the second part of the first cut), the third is done to a rod of length 4 and the last cut is to a rod of length 3. The total cost is 7 + 6 + 4 + 3 = 20.
 * Rearranging the cuts to be [1, 3, 4, 5] for example will lead to a scenario with total cost = 16 (as shown in the figure above).
 *
 * Example 2:
 * Input: n = 9, cuts = [5,6,1,4,2]
 * Output: 22
 * Explanation: The cuts are shown in the figure above.
 * For example, the first cut is done to a rod of length 9 so the cost is 9. The second cut is done to a rod of length 8 (i.e. the second part of the first cut), the third is done to a rod of length 6 and the last cut is to a rod of length 4. The total cost is 9 + 8 + 6 + 4 = 28.
 * Rearranging the cuts to be [6, 5, 4, 2, 1] for example will lead to a scenario with total cost = 22 which is the minimum possible.
 * 
 * Constraints:
 * 2 <= n <= 10^6
 * 1 <= cuts.length <= min(n - 1, 100)
 * 1 <= cuts[i] <= n - 1
 * All the integers in cuts array are distinct.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        // Add the endpoints
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());

        int m = cuts.size();
        // dp[i][j] = min cost to cut between cuts[i] and cuts[j]
        vector<vector<int>> dp(m, vector<int>(m, 0));

        // len is the distance in indices (j - i)
        for (int len = 2; len < m; ++len) {            // we need at least one cut between i and j
            for (int i = 0; i + len < m; ++i) {
                int j = i + len;
                dp[i][j] = INT_MAX;
                // Try every possible first cut between i and j
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] = min(dp[i][j],
                                   cuts[j] - cuts[i] + dp[i][k] + dp[k][j]);
                }
            }
        }
        return dp[0][m - 1];
    }
};
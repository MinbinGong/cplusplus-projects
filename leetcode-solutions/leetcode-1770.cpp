/**
 * 1770. Maximum Score from Performing Multiplication Operations
 * 
 * You are given two integer arrays nums and multipliers of size n and m respectively, where n >= m. The arrays are 1-indexed.
 * 
 * You begin with a score of 0. You want to perform exactly m operations. On the ith operation (1-indexed), you will:
 * 
 * Choose one integer x from either the start or the end of the array nums.
 * Add multipliers[i] * x to your score.
 * Remove x from the array nums.
 * Return the maximum score after performing m operations.
 * 
 * Example 1:
 * 
 * Input: nums = [1,2,3], multipliers = [3,2,1]
 * Output: 14
 * Explanation: An optimal solution is as follows:
 * - Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
 * - Choose from the end, [1], adding 1 * 1 = 1 to the score.
 * The total score is 9 + 4 + 1 = 14.
 * 
 * Example 2:
 * 
 * Input: nums = [-5,-3,-3,-2,7,1], multipliers = [-10,-5,3,4,6]
 * Output: 102
 * Explanation: An optimal solution is as follows:
 * - Choose from the start, [-5,-3,-3,-2,7,1], adding -5 * -10 = 50 to the score.
 * - Choose from the start, [-3,-3,-2,7,1], adding -3 * -5 = 15 to the score.
 * - Choose from the start, [-3,-2,7,1], adding -3 * 3 = -9 to the score.
 * - Choose from the end, [-2,7,1], adding 1 * 4 = 4 to the score. 
 * - Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
 * 
 * Constraints:
 * 
 * n == nums.length
 * m == multipliers.length
 * 1 <= m <= 103
 * m <= n <= 105
 * -1000 <= nums[i], multipliers[i] <= 1000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int n = nums.size();
        int m = multipliers.size();
        
        // dp[i][j] = maximum score after taking i elements from the left
        // and j elements from the right (i + j operations performed)
        vector<vector<int>> dp(m + 1, vector<int>(m + 1, INT_MIN));
        dp[0][0] = 0;
        
        int ans = INT_MIN;
        
        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j <= m - i; ++j) {
                int k = i + j;          // number of operations already done
                if (k == m) {            // all multipliers used
                    ans = max(ans, dp[i][j]);
                    continue;
                }
                // Option 1: take the next element from the left end
                dp[i + 1][j] = max(dp[i + 1][j],
                                   dp[i][j] + nums[i] * multipliers[k]);
                
                // Option 2: take the next element from the right end
                dp[i][j + 1] = max(dp[i][j + 1],
                                   dp[i][j] + nums[n - 1 - j] * multipliers[k]);
            }
        }
        
        return ans;
    }
};

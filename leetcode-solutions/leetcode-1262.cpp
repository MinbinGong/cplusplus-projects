/**
 * 1262. Greatest Sum Divisible by Three
 * 
 * Given an array nums of integers, we need to find the maximum possible sum of elements of the array such that it is divisible by three.
 * 
 * Example 1:
 * Input: nums = [3,6,5,1,8]
 * Output: 18
 * Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).
 * 
 * Example 2:
 * Input: nums = [4]
 * Output: 0
 * Explanation: Since 4 is not divisible by 3, do not pick any number.
 * 
 * Example 3:
 * Input: nums = [1,2,3,4,4]
 * Output: 12
 * Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).
 * 
 * Note:
 * 1 <= nums.length <= 4 * 10^4
 * 1 <= nums[i] <= 10^4
 * 
 */
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        // dp[r] = maximum sum that gives remainder r (r = 0,1,2)
        // Initialize with -1 meaning state not reachable.
        vector<int> dp(3, -1);
        dp[0] = 0;  // sum 0 is reachable with remainder 0

        for (int num : nums) {
            vector<int> new_dp = dp;  // start with old values
            for (int r = 0; r < 3; ++r) {
                if (dp[r] != -1) {               // if this remainder state is reachable
                    int sum = dp[r] + num;
                    int new_r = sum % 3;
                    if (new_r < 0) new_r += 3;   // make remainder non‑negative
                    new_dp[new_r] = max(new_dp[new_r], sum);
                }
            }
            dp = move(new_dp);
        }

        return dp[0];   // max sum divisible by 3
    }
};
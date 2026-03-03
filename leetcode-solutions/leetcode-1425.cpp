/**
 * 1425. Constrained Subsequence Sum
 * 
 * Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array such that for every two consecutive integers in the subsequence, nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.
 * 
 * A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.
 * 
 * Example 1:
 * 
 * Input: nums = [10,2,-10,5,20], k = 2
 * Output: 37
 * Explanation: The subsequence is [10, 2, 5, 20].
 * 
 * Example 2:
 * 
 * Input: nums = [-1,-2,-3], k = 1
 * Output: -1
 * Explanation: The subsequence must be non-empty, so we choose the largest number.
 * 
 * Example 3:
 * 
 * Input: nums = [10,-2,-10,-5,20], k = 2
 * Output: 23
 * Explanation: The subsequence is [10, -2, -5, 20].
 * 
 * Note:
 * 1 <= k <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 
 */
#include <vector>
#include <deque>
#include <numeric>
using namespace std;

class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n);           // dp[i] = max sum ending at i
        deque<int> dq;                // stores indices, with decreasing dp values
        int ans = nums[0];            // at least one element

        for (int i = 0; i < n; ++i) {
            // Remove indices out of the sliding window (distance > k)
            while (!dq.empty() && dq.front() < i - k)
                dq.pop_front();

            // Best previous dp in the window (if any)
            int bestPrev = dq.empty() ? 0 : dp[dq.front()];
            dp[i] = nums[i] + max(0, bestPrev);
            ans = max(ans, dp[i]);

            // Maintain deque in decreasing order of dp
            while (!dq.empty() && dp[dq.back()] <= dp[i])
                dq.pop_back();
            dq.push_back(i);
        }
        return ans;
    }
};
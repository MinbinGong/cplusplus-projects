/*
 * Maximum Lenght of Repeated Subarray
 *
 * Given two integer arrays nums1 and nums2, return the maximum length of a subarray that appears in both arrays.
 * 
 * Example 1:
 * 
 * Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
 * Output: 3
 * Explanation: The repeated subarray with maximum length is [3,2,1].
 * 
 * Example 2:
 * 
 * Input: nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0]
 * Output: 5
 * 
 * Note:
 * 
 * 1 <= nums1.length, nums2.length <= 1000.
 * 0 <= nums1[i], nums2[i] <= 100.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        // dp[j] represents the length of common subarray ending at nums1[i-1] and nums2[j-1]
        vector<int> dp(m + 1, 0);
        int ans = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = m; j >= 1; --j) { // traverse backwards to use previous row's values
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[j] = dp[j - 1] + 1;
                    ans = max(ans, dp[j]);
                } else {
                    dp[j] = 0; // reset because subarray must be contiguous
                }
            }
        }
        return ans;
    }
};
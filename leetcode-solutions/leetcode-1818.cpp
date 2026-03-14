/*
 * 1818. Minimum Absolute Sum Difference
 * 
 * You are given two positive integer arrays nums1 and nums2, both of length n.
 * 
 * The absolute sum difference of arrays nums1 and nums2 is defined as the sum of |nums1[i] - nums2[i]| for each 0 <= i < n (0-indexed).
 * 
 * You can replace at most one element of nums1 with any other element in nums1 to minimize the absolute sum difference.
 * 
 * Return the minimum absolute sum difference after replacing at most one element in the array nums1. Since the answer may be large, return it modulo 109 + 7.
 * 
 * |x| is defined as:
 * 
 * x if x >= 0, or
 * -x if x < 0.
 * 
 * Example 1:
 * Input: nums1 = [1,7,5], nums2 = [2,3,5]
 * Output: 3
 * Explanation: There are two possible optimal solutions:
 * - Replace the second element with the first: nums1 = [2,7,5], nums2 = [2,3,5], |2-2| + |7-3| + |5-5| = 0 + 4 + 0 = 4.
 * - Replace the second element with the third: nums1 = [1,5,5], nums2 = [2,3,5], |1-2| + |5-3| + |5-5| = 1 + 2 + 0 = 3.
 * 
 * Example 2:
 * Input: nums1 = [2,4,6,8,10], nums2 = [2,4,6,8,10]
 * Output: 0
 * Explanation: nums1 is equal to nums2 so no replacement is needed. This will result in an absolute sum difference of 0.
 * 
 * Constraints:
 * 
 * n == nums1.length
 * n == nums2.length
 * 1 <= n <= 105
 * 1 <= nums1[i], nums2[i] <= 105
 * 
 */
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        const int MOD = 1e9 + 7;
        int n = nums1.size();
        vector<int> sorted = nums1;
        sort(sorted.begin(), sorted.end());
        
        long long total = 0;
        int maxReduction = 0;
        
        for (int i = 0; i < n; ++i) {
            int a = nums1[i];
            int b = nums2[i];
            int diff = abs(a - b);
            total += diff;
            
            // Find the element in sorted that is closest to b
            auto it = lower_bound(sorted.begin(), sorted.end(), b);
            int best = diff; // default to current diff
            if (it != sorted.end()) {
                best = min(best, abs(*it - b));
            }
            if (it != sorted.begin()) {
                --it;
                best = min(best, abs(*it - b));
            }
            
            int reduction = diff - best;
            if (reduction > maxReduction) {
                maxReduction = reduction;
            }
        }
        
        long long ans = (total - maxReduction) % MOD;
        if (ans < 0) ans += MOD;
        return (int)ans;
    }
};
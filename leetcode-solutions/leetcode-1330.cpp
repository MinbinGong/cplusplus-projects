/*
 * 1330. Reverse Subarray To Maximize Array Value
 *
 * You are given an integer array nums. The value of this array is defined as the sum of |nums[i] - nums[i + 1]| for all 0 <= i < nums.length - 1.
 *
 * You are allowed to select any subarray of the given array and reverse it. You can perform this operation only once.
 *
 * Find maximum possible value of the final array.
 *
 * Example 1:
 * Input: nums = [2,3,1,5,4]
 * Output: 10
 * Explanation: By reversing the subarray [3,1,5] the array becomes [2,5,1,3,4] whose value is 10.
 *
 * Example 2:
 * Input: nums = [2,4,9,24,2,1,10]
 * Output: 68
 * 
 * Note:
 * 1 <= nums.length <= 3 * 10^4
 * -10^5 <= nums[i] <= 10^5
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;
        
        // original total value
        int base = 0;
        for (int i = 1; i < n; ++i) {
            base += abs(nums[i] - nums[i-1]);
        }
        
        int best = 0;
        
        // reversals that touch the left or right boundary
        for (int i = 1; i < n-1; ++i) {
            // reverse [0, i]
            best = max(best, abs(nums[0] - nums[i+1]) - abs(nums[i] - nums[i+1]));
            // reverse [i, n-1]
            best = max(best, abs(nums[n-1] - nums[i-1]) - abs(nums[i] - nums[i-1]));
        }
        
        // interior case: reverse a subarray that does not touch boundaries
        int minMax = INT_MAX;   // smallest of the two larger numbers in an edge
        int maxMin = INT_MIN;   // largest of the two smaller numbers in an edge
        for (int i = 0; i < n-1; ++i) {
            int a = nums[i], b = nums[i+1];
            minMax = min(minMax, max(a, b));
            maxMin = max(maxMin, min(a, b));
        }
        best = max(best, 2 * (maxMin - minMax));
        
        return base + best;
    }
};
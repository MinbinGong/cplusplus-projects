/*
 * Continuous Subarray Sum
 *
 * Given an integer array nums and an integer k, return true if nums has a continuous subarray of size at least two whose elements sum up to a multiple of k, or false otherwise.
 * 
 * An integer x is a multiple of k if there exists an integer n such that x = n * k. 0 is always a multiple of k.
 * 
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^9
 * 0 <= sum(nums[i]) <= 2^31 - 1
 * 1 <= k <= 2^31 - 1
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        if (n < 2) return false;

        unordered_map<int, int> seen;  // remainder -> first index
        seen[0] = -1;                  // handle subarrays starting from index 0

        int prefix = 0;
        for (int i = 0; i < n; ++i) {
            prefix += nums[i];

            int remainder;
            if (k == 0) {
                remainder = prefix;      // for k=0, we need sum == 0 → prefix equal
            } else {
                remainder = prefix % k;
                if (remainder < 0) remainder += k; // ensure non-negative
            }

            if (seen.count(remainder)) {
                if (i - seen[remainder] >= 2)
                    return true;
            } else {
                seen[remainder] = i;
            }
        }
        return false;
    }
};
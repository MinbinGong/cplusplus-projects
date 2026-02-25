/**
 * 982. Triples with Bitwise AND Equal To Zero
 *
 * Given an array of integers nums, return the number of triples of indices (i, j, k) such that:
 *
 * 0 <= i < nums.length
 * 0 <= j < nums.length
 * 0 <= k < nums.length
 * nums[i] & nums[j] & nums[k] == 0, where & represents the bitwise-AND operator.
 * 
 * Example 1:
 *
 * Input: nums = [2,1,3]
 * Output: 12
 * Explanation: We could choose the following i, j, k triples:
 * (i=0, j=0, k=1) : 2 & 2 & 1
 * (i=0, j=1, k=0) : 2 & 1 & 2
 * (i=0, j=1, k=1) : 2 & 1 & 1
 * (i=0, j=1, k=2) : 2 & 1 & 3
 * (i=0, j=2, k=1) : 2 & 3 & 1
 * (i=1, j=0, k=0) : 1 & 2 & 2
 * (i=1, j=0, k=1) : 1 & 2 & 1
 * (i=1, j=1, k=0) : 1 & 1 & 2
 * (i=1, j=2, k=0) : 1 & 3 & 2
 * (i=2, j=0, k=1) : 3 & 2 & 1
 * (i=2, j=1, k=0) : 3 & 1 & 2
 * 
 * Example 2:
 *
 * Input: nums = [0,0,0]
 * Output: 27
 * 
 * Note:
 *
 * 1 <= nums.length <= 1000
 * 0 <= nums[i] < 2^16
 */
#include <vector>
using namespace std;

class Solution {
public:
    int countTriplets(vector<int>& nums) {
        const int MAX_VAL = 1 << 16;          // 2^16 = 65536
        vector<int> cnt(MAX_VAL, 0);           // count of each AND of two numbers
        int n = nums.size();

        // Count all ordered pairs (i, j)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ++cnt[nums[i] & nums[j]];
            }
        }

        int ans = 0;
        // For each third element, add counts of all v such that (v & nums[k]) == 0
        for (int k = 0; k < n; ++k) {
            for (int v = 0; v < MAX_VAL; ++v) {
                if ((v & nums[k]) == 0) {
                    ans += cnt[v];
                }
            }
        }
        return ans;
    }
};
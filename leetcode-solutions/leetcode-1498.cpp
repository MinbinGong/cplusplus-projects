/*
 * 1498. Number of Subsequences That Satisfy the Given Sum Condition
 *
 * Given an array of integers nums and an integer target.
 *
 * Return the number of non-empty subsequences of nums such that the sum of the minimum and maximum element on it is less or equal to target.
 *
 * Since the answer may be too large, return it modulo 10^9 + 7.
 *
 * Example 1:
 * Input: nums = [3,5,6,7], target = 9
 * Output: 4
 * Explanation: There are 4 subsequences that satisfy the condition.
 * [3] -> Min value + max value <= target (3 + 3 <= 9)
 * [3,5] -> (3 + 5 <= 9)
 * [3,5,6] -> (3 + 6 <= 9)
 * [3,6] -> (3 + 6 <= 9)
 *
 * Example 2:
 * Input: nums = [3,3,6,8], target = 10
 * Output: 6
 * Explanation: There are 6 subsequences that satisfy the condition. (nums can have repeated numbers).
 * [3] , [3] , [3,3], [3,6] , [3,6] , [3,3,6]
 *
 * constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^6
 * 1 <= target <= 10^6
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        sort(nums.begin(), nums.end());

        // pre‑compute powers of two modulo MOD
        vector<int> pow2(n);
        pow2[0] = 1;
        for (int i = 1; i < n; ++i) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        int ans = 0;
        int j = n - 1;                     // right pointer

        for (int i = 0; i < n; ++i) {
            // shrink j until the pair (nums[i], nums[j]) satisfies the condition
            while (j >= i && nums[i] + nums[j] > target) {
                --j;
            }
            if (j < i) break;              // no more valid pairs for larger i

            // all subsequences with first element i and last element ≤ j are valid
            ans = (ans + pow2[j - i]) % MOD;
        }

        return ans;
    }
};
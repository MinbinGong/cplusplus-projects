/**
 * 891. Sum of Subsequence Widths
 *
 * Given an array of integers A, consider all non-empty subsequences of A.
 * For any sequence S, let the width of S be the difference between the maximum and minimum element of S.
 * Return the sum of the widths of all subsequences of A.
 * As the answer may be very large, return the answer modulo 10^9 + 7.
 *
 * Example 1:
 * Input: [2,1,3]
 * Output: 6
 * Explanation:
 * Subsequences are [1], [2], [3], [2,1], [2,3], [1,3], [2,1,3].
 * The corresponding widths are 0, 0, 0, 1, 1, 2, 2.
 * The sum of these widths is 6.
 *
 * Note:
 * 1 <= A.length <= 20000
 * 1 <= A[i] <= 20000
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int sumSubseqWidths(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<long long> pow2(n);
        pow2[0] = 1;
        for (int i = 1; i < n; ++i) {
            pow2[i] = (pow2[i-1] * 2) % MOD;
        }
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            long long left = pow2[i];          // 左边元素可选个数
            long long right = pow2[n-1-i];     // 右边元素可选个数
            ans = (ans + nums[i] * (left - right)) % MOD;
        }
        return (ans + MOD) % MOD; // 保证非负
    }
};
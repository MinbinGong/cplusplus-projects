/*
 * 1191. K-Concatenation Maximum Sum
 *
 * Given an integer array arr and an integer k, modify the array by repeating it k times.
 * 
 * For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].
 * 
 * Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can be 0 and its sum in that case is 0.
 * 
 * As the answer can be very large, return the answer modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: arr = [1,2], k = 3
 * Output: 9
 * 
 * Example 2:
 * Input: arr = [1,-2,1], k = 5
 * Output: 2
 * 
 * Example 3:
 * Input: arr = [-1,-2], k = 7
 * Output: 0
 * 
 * Note:
 * 1 <= arr.length <= 10^5
 * 1 <= k <= 10^5
 * -10^4 <= arr[i] <= 10^4
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        const int MOD = 1e9 + 7;
        long long max1 = 0, cur = 0;          // 单个数组的最大子数组和（Kadane）
        for (int x : arr) {
            cur = max((long long)x, cur + x);
            max1 = max(max1, cur);
        }
        if (k == 1) return max1 % MOD;

        long long total = 0;                   // 整个数组的和
        for (int x : arr) total += x;

        long long prefix = 0, suffix = 0;
        long long prefix_max = 0, suffix_max = 0; // 前缀最大和、后缀最大和
        for (int i = 0; i < arr.size(); ++i) {
            prefix += arr[i];
            prefix_max = max(prefix_max, prefix);
        }
        for (int i = arr.size() - 1; i >= 0; --i) {
            suffix += arr[i];
            suffix_max = max(suffix_max, suffix);
        }

        long long two = suffix_max + prefix_max;   // 两个数组拼接的最大子数组和
        long long ans = max(max1, two);

        if (total > 0) {                           // 只有总和为正时，中间加整段才有意义
            long long many = two + (k - 2) * total; // 多个数组拼接的最大和
            ans = max(ans, many);
        }

        return ans % MOD;
    }
};
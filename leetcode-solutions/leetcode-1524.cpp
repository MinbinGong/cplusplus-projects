/*
 * 1524. Number of Sub-arrays With Odd Sum
 *
 * Given an array of integers arr, return the number of sub-arrays with an odd sum.
 *
 * Since the answer can be very large, return it modulo 10^9 + 7.
 *
 * Example 1:
 * Input: arr = [1,3,5]
 * Output: 4
 * Explanation: All sub-arrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
 * All sub-arrays sum are [1,4,9,3,8,5].
 * Odd sums are [1,9,3,5] so the answer is 4.
 * 
 * Example 2:
 * Input: arr = [2,4,6]
 * Output: 0
 * Explanation: All sub-arrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
 * All sub-arrays sum are [2,6,12,4,10,6].
 * Even sums are [2,6,12,10,6] so the answer is 0.
 * 
 * Constraints:
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 10^6
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        int oddCount = 0, evenCount = 1; // prefix sum parity counts, start with 0 (even)
        int prefix = 0;
        long long ans = 0;

        for (int num : arr) {
            prefix = (prefix + num) & 1; // update parity (0 even, 1 odd)
            if (prefix) { // current prefix is odd
                ans = (ans + evenCount) % MOD;
                oddCount++;
            } else { // current prefix is even
                ans = (ans + oddCount) % MOD;
                evenCount++;
            }
        }
        return ans;
    }
};
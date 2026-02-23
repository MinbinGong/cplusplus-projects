/*
 * Maximum Sum of 3 Non-Overlapping Subarrays
 *
 * In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.
 *
 * Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.
 *
 * Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.
 * 
 * Example:
 *
 * Input: [1,2,1,2,6,7,5,1], 2
 * Output: [0, 3, 5]
 * Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
 * We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
 * 
 * Note:
 *
 * nums.length will be between 1 and 20000.
 * nums[i] will be between 1 and 65535.
 * k will be between 1 and floor(nums.length / 3).
 * 
 */
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        // prefix sums to compute subarray sums quickly
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        // sum[i] = sum of subarray starting at i, length k
        vector<int> sum(n - k + 1, 0);
        for (int i = 0; i <= n - k; ++i) {
            sum[i] = prefix[i + k] - prefix[i];
        }
        int m = sum.size(); // number of possible subarrays

        // left[i]: best index (smallest) among [0..i] with maximum sum
        vector<int> left(m);
        left[0] = 0;
        for (int i = 1; i < m; ++i) {
            if (sum[i] > sum[left[i - 1]]) {
                left[i] = i;
            } else {
                left[i] = left[i - 1];
            }
        }

        // right[i]: best index (smallest) among [i..m-1] with maximum sum
        vector<int> right(m);
        right[m - 1] = m - 1;
        for (int i = m - 2; i >= 0; --i) {
            if (sum[i] >= sum[right[i + 1]]) { // >= to choose smaller index when tie
                right[i] = i;
            } else {
                right[i] = right[i + 1];
            }
        }

        int bestTotal = -1;
        vector<int> ans(3);
        // middle subarray must start at least k from left and at least k from right
        for (int j = k; j <= m - 1 - k; ++j) {
            int i = left[j - k];
            int l = right[j + k];
            int total = sum[i] + sum[j] + sum[l];
            if (total > bestTotal) {
                bestTotal = total;
                ans = {i, j, l};
            } else if (total == bestTotal) {
                // lexicographic comparison
                if (i < ans[0] || (i == ans[0] && j < ans[1]) || (i == ans[0] && j == ans[1] && l < ans[2])) {
                    ans = {i, j, l};
                }
            }
        }
        return ans;
    }
};
/**
 * 1508. Range Sum of Sorted Subarray Sums
 * 
 * You are given the array nums consisting of n positive integers.
 * You computed the sum of all non-empty continuous subarrays from the array and then sorted them in non-decreasing order, creating a new array of n * (n + 1) / 2 numbers.
 * Return the sum of the numbers from index left to index right (indexed from 1), inclusive, in the new array.
 * Since the answer can be a huge number return it modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: nums = [1,2,3,4], n = 4, left = 1, right = 5
 * Output: 13 
 * Explanation: All subarray sums are 1, 3, 6, 10, 2, 5, 9, 3, 7, 4. After sorting them in non-decreasing order we have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 1 to ri = 5 is 1 + 2 + 3 + 3 + 4 = 13. 
 * 
 * Example 2:
 * Input: nums = [1,2,3,4], n = 4, left = 3, right = 4
 * Output: 6
 * Explanation: The given array is the same as example 1. We have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 3 to ri = 4 is 3 + 3 = 6.
 * 
 * Example 3:
 * Input: nums = [1,2,3,4], n = 4, left = 1, right = 10
 * Output: 50
 * 
 * Note:
 * 1 <= nums.length <= 10^3
 * 1 <= nums[i] <= 100
 * 1 <= left <= right <= n * (n + 1) / 2
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        const int MOD = 1000000007;
        // 计算前缀和
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        
        // 二分查找第k小的子数组和
        auto countLessOrEqual = [&](long long target) -> pair<long long, int> {
            long long sum = 0;
            int count = 0;
            int j = 0;
            for (int i = 0; i < n; i++) {
                while (j <= n && prefix[j] - prefix[i] <= target) {
                    j++;
                }
                // j-1是满足条件的最后一个索引
                count += j - i - 1;
                // 计算这些子数组和的和
                sum += prefix[j - 1] * (j - i - 1) - (j - i - 1) * prefix[i];
            }
            return {sum, count};
        };
        
        // 查找第right小的子数组和
        long long lo = 1, hi = prefix[n];
        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (countLessOrEqual(mid).second < right) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        long long rightSum = countLessOrEqual(lo).first;
        int rightCount = countLessOrEqual(lo).second;
        
        // 查找第left-1小的子数组和
        lo = 1;
        hi = prefix[n];
        if (left > 1) {
            while (lo < hi) {
                long long mid = lo + (hi - lo) / 2;
                if (countLessOrEqual(mid).second < left - 1) {
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
            }
        }
        long long leftSum = (left > 1) ? countLessOrEqual(lo).first : 0;
        int leftCount = (left > 1) ? countLessOrEqual(lo).second : 0;
        
        // 调整结果（可能有多余的）
        long long result = rightSum - leftSum;
        if (rightCount > right) {
            result -= lo * (rightCount - right);
        }
        if (leftCount > left - 1) {
            result += lo * (leftCount - (left - 1));
        }
        
        return (result % MOD + MOD) % MOD;
    }
};
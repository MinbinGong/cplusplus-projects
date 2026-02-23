/*
 * Subarray Product Less Than K
 *
 * Input: nums = [10, 5, 2, 6], k = 100
 * Output: 8
 * Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
 * Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
 * 
 * Note:
 * 1. 0 < nums.length <= 50000.
 * 2. 0 < nums[i] < 1000.
 * 3. 0 <= k < 10^6.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0; // 因为所有数都是正整数，乘积至少为1，k≤1时不可能有解
        int n = nums.size();
        int left = 0;
        long long product = 1;
        int count = 0;
        for (int right = 0; right < n; ++right) {
            product *= nums[right];
            while (product >= k) {
                product /= nums[left];
                left++;
            }
            // 当前窗口内所有以 right 结尾的子数组都满足条件，个数为窗口长度
            count += right - left + 1;
        }
        return count;
    }
};
/**
 * 974. Subarray Sums Divisible by K
 *
 * Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.
 *
 * A subarray is a contiguous part of an array.
 *
 * Example 1:
 *
 * Input: nums = [4,5,0,-2,-3,1], k = 5
 * Output: 7
 * Explanation: There are 7 subarrays with a sum divisible by k = 5:
 * [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
 * 
 * Example 2:
 *
 * Input: nums = [5], k = 9
 * Output: 0
 * 
 * Note:
 *
 * 1 <= nums.length <= 3 * 104
 * -104 <= nums[i] <= 104
 * 1 <= k <= 104
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        unordered_map<int, int> remainderCount;
        remainderCount[0] = 1; // 初始化空前缀和，余数0出现1次
        int prefixSum = 0;
        int count = 0;
        
        for (int num : nums) {
            prefixSum += num;
            int remainder = prefixSum % k;
            // 调整余数为非负数
            if (remainder < 0) {
                remainder += k;
            }
            // 累加之前相同余数出现的次数
            if (remainderCount.find(remainder) != remainderCount.end()) {
                count += remainderCount[remainder];
            }
            // 更新当前余数计数
            remainderCount[remainder]++;
        }
        
        return count;
    }
};
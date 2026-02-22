/*
 * Maximum Product of Three Numbers
 * 
 * Given an integer array nums, find three numbers whose product is maximum and return the maximum product.
 * 
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: 6
 * 
 * Example 2:
 * Input: nums = [1,2,3,4]
 * Output: 24
 * 
 * Example 3:
 * Input: nums = [-1,-2,-3]
 * Output: -6
 * 
 * Constraints:
 * 3 <= nums.length <= 104
 * -1000 <= nums[i] <= 1000
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        // 初始化最大值
        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        // 初始化最小值
        int min1 = INT_MAX, min2 = INT_MAX;
        
        for (int num : nums) {
            // 更新最大的三个数
            if (num > max1) {
                max3 = max2;
                max2 = max1;
                max1 = num;
            } else if (num > max2) {
                max3 = max2;
                max2 = num;
            } else if (num > max3) {
                max3 = num;
            }
            
            // 更新最小的两个数
            if (num < min1) {
                min2 = min1;
                min1 = num;
            } else if (num < min2) {
                min2 = num;
            }
        }
        
        // 返回两种可能的最大值
        return max(max1 * max2 * max3, max1 * min1 * min2);
    }
};
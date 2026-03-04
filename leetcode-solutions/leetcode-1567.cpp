/*
 * 1567. Maximum Length of Subarray With Positive Product
 * 
 * Given an array of integers nums, find the maximum length of a subarray where the product of all its elements is positive.
 * 
 * A subarray of an array is a consecutive sequence of zero or more values taken out of that array.
 * 
 * Return the maximum length of a subarray with positive product.
 * 
 * Example 1:
 * Input: nums = [1,-2,-3,4]
 * Output: 4
 * Explanation: The array nums already has a positive product of 24.
 * 
 * Example 2:
 * Input: nums = [0,1,-2,-3,-4]
 * Output: 3
 * Explanation: The longest subarray with positive product is [1,-2,-3] which has a product of 6.
 * Notice that we cannot include 0 in the subarray since that'll make the product 0 which is not positive.
 * 
 * Example 3:
 * Input: nums = [-1,-2,-3,0,1]
 * Output: 2
 * Explanation: The longest subarray with positive product is [-1,-2] or [-2,-3].
 * 
 * Constraints:
 * 1 <= nums.length <= 10^5
 * -10^9 <= nums[i] <= 10^9
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int pos = 0, neg = 0; // 以当前元素结尾的乘积为正/负的最长长度
        int ans = 0;
        for (int x : nums) {
            if (x > 0) {
                // 正数：正数长度+1，负数长度若存在则+1否则为0
                pos = pos + 1;
                neg = (neg == 0 ? 0 : neg + 1);
            } else if (x < 0) {
                // 负数：原来的正数变负数，负数变正数，然后分别+1
                int new_pos = (neg == 0 ? 0 : neg + 1);
                int new_neg = pos + 1;
                pos = new_pos;
                neg = new_neg;
            } else { // x == 0
                // 遇到0，乘积归零，长度重置
                pos = 0;
                neg = 0;
            }
            ans = max(ans, pos);
        }
        return ans;
    }
};

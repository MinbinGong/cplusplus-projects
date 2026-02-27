/**
 * 1150. Check If a Number Is Majority Element in a Sorted Array
 * Easy
 * 
 * (This problem is an interactive problem.)
 * 
 * Given an array nums sorted in non-decreasing order, and a number target, return True if and only if target is a majority element.
 * 
 * A majority element is an element that appears more than N/2 times in an array of length N.
 * 
 * Example 1:
 * Input: nums = [2,4,5,5,5,5,5,6,6], target = 5
 * Output: true
 * Explanation: 
 * The value 5 appears 5 times and the length of the array is 9.
 * Thus, 5 is a majority element because 5 > 9/2 is true.
 * 
 * Example 2:
 * Input: nums = [10,100,101,101], target = 101
 * Output: false
 * Explanation: 
 * The value 101 appears 2 times and the length of the array is 4.
 * 
 * Note:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 10^9
 * nums is sorted in non-decreasing order.
 * 
 */
class Solution {
public:
    bool isMajorityElement(vector<int>& nums, int target) {
        int n = nums.size();
        auto first = lower_bound(nums.begin(), nums.end(), target);
        if (first == nums.end() || *first != target) return false;
        auto last = upper_bound(nums.begin(), nums.end(), target);
        int count = last - first;
        return count > n / 2;
    }
};
/*
 * Shortest Unsorted Continuous Subarray
 *
 * Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.
 * 
 * You need to find the shortest such subarray and output its length.
 * 
 * Example:
 * Input: [2, 6, 4, 8, 10, 9, 15]
 * Output: 5
 * Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
 * 
 * Note:
 * Then length of the input array is in range [1, 10,000].
 * The input array may contain duplicates, so ascending order here means <=.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n - 1;
        
        // Find first index where order breaks from left
        while (left < n - 1 && nums[left] <= nums[left + 1]) left++;
        if (left == n - 1) return 0; // already sorted
        
        // Find first index where order breaks from right
        while (right > 0 && nums[right] >= nums[right - 1]) right--;
        
        // Find min and max in the candidate subarray [left, right]
        int minVal = INT_MAX, maxVal = INT_MIN;
        for (int i = left; i <= right; ++i) {
            minVal = min(minVal, nums[i]);
            maxVal = max(maxVal, nums[i]);
        }
        
        // Expand left if any element to the left is greater than minVal
        while (left > 0 && nums[left - 1] > minVal) left--;
        // Expand right if any element to the right is less than maxVal
        while (right < n - 1 && nums[right + 1] < maxVal) right++;
        
        return right - left + 1;
    }
};
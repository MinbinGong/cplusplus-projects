/*
 * Valid Triangle Number
 * 
 * Given an array consists of non-negative integers, your task is to count the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.
 * 
 * Example 1:
 * Input: [2,2,3,4]
 * Output: 3
 * Explanation:
 * Valid combinations are: 
 * 2,3,4 (using the first 2)
 * 2,3,4 (using the second 2)
 * 2,2,3
 * 
 * Note:
 * 1. The length of the given array won't exceed 1000.
 * 2. The integers in the given array are in the range of [0, 1000].
 * 
 */
#include <vector>
#include <algorithm>

class Solution {
public:
    int triangleNumber(std::vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        
        std::sort(nums.begin(), nums.end());
        int count = 0;
        
        // Fix the largest side
        for (int i = n - 1; i >= 2; --i) {
            int left = 0, right = i - 1;
            while (left < right) {
                if (nums[left] + nums[right] > nums[i]) {
                    // All pairs (left, right) with left' from left to right-1 work
                    count += (right - left);
                    --right;
                } else {
                    ++left;
                }
            }
        }
        return count;
    }
};
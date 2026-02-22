/*
 * 540. Single Element in a Sorted Array
 * 
 * You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.
 * 
 * Return the single element that appears only once.
 * 
 * Your solution must run in O(log n) time and O(1) space.
 * 
 * Example 1:
 * Input: nums = [1,1,2,3,3,4,4,8,8]
 * Output: 2
 * 
 * Example 2:
 * Input: nums = [3,3,7,7,10,11,11]
 * Output: 10
 * 
 * Constraints:
 * 1. 1 <= nums.length <= 105
 * 2. 0 <= nums[i] <= 105
 * 3. All the values of nums are unique.
 * 4. nums[i] == nums[i+1] for all valid i.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            // Ensure mid is even for comparison with next
            if (mid % 2 == 1) mid--;
            if (nums[mid] == nums[mid + 1]) {
                left = mid + 2; // single element is on the right
            } else {
                right = mid; // single element is on the left (including mid)
            }
        }
        return nums[left];
    }
};

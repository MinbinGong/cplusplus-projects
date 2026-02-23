/*
 * Find Pivot Index
 *
 * Given an array of integers nums, write a method that returns the "pivot" index of this array.
 * 
 * We define the pivot index as the index where the sum of the numbers to the left of the index is equal to the sum of the numbers to the right of the index.
 * 
 * If no such index exists, we should return -1. If there are multiple pivot indexes, you should return the left-most pivot index.
 * 
 * Note:
 * 1. The length of nums will be in the range [0, 10000].
 * 2. Each element nums[i] will be an integer in the range [-1000, 1000].
 * 3. The sum of nums will not exceed 10000.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }
        int leftSum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (leftSum == totalSum - leftSum - nums[i]) {
                return i;
            }
            leftSum += nums[i];
        }
        return -1;
    }
};
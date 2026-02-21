/*
 *
 *  Find Maximum Consecutive Ones
 *
 *  Given a binary array nums, return the maximum number of consecutive 1's in the array.
 *
 *  Constraints:
 *  1 <= nums.length <= 105
 *  nums[i] is either 0 or 1.
 * 
 */
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int maxCount = 0, count = 0;
        for (int num : nums) {
            if (num == 1) {
                count++;
                maxCount = max(maxCount, count);
            } else {
                count = 0;
            }
        }
        return maxCount;
    }
};
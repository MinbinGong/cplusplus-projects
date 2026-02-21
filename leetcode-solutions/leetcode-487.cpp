/*
 *  Max Consecutive Ones II
 *
 *  Given a binary array nums, return the maximum number of consecutive 1's in the array if you can flip at most one 0.
 *
 *  Constraints:
 *  1 <= nums.length <= 105
 *  nums[i] is either 0 or 1.
 * 
 */
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int left = 0, zeros = 0, maxLen = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) zeros++;
            // shrink window if too many zeros
            while (zeros > 1) {
                if (nums[left] == 0) zeros--;
                left++;
            }
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};
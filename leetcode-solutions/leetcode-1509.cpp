/**
 * 1509. Minimum Difference Between Largest and Smallest Value in Three Moves
 * 
 * You are given an integer array nums.
 * In one move, you can choose one element of nums and change it to any value.
 * Return the minimum difference between the largest and smallest value of nums after performing at most three moves.
 * 
 * Example 1:
 * Input: nums = [5,3,2,4]
 * Output: 0
 * Explanation: We can make at most 3 moves.
 * In the first move, change 2 to 3. nums becomes [5,3,3,4].
 * In the second move, change 4 to 3. nums becomes [5,3,3,3].
 * In the third move, change 5 to 3. nums becomes [3,3,3,3].
 * After performing 3 moves, the difference between the minimum and maximum is 3 - 3 = 0.
 * 
 * Example 2:
 * Input: nums = [1,5,0,10,14]
 * Output: 1
 * Explanation: We can make at most 3 moves.
 * In the first move, change 5 to 0. nums becomes [1,0,0,10,14].
 * In the second move, change 10 to 0. nums becomes [1,0,0,0,14].
 * In the third move, change 14 to 1. nums becomes [1,0,0,0,1].
 * After performing 3 moves, the difference between the minimum and maximum is 1 - 0 = 1.
 * 
 * Example 3:
 * Input: nums = [3,100,20]
 * Output: 0
 * 
 * Note:
 * 1 <= nums.length <= 10^4
 * -10^9 <= nums[i] <= 10^9
 * 
 */
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        if (n <= 4) return 0;
        sort(nums.begin(), nums.end());
        int ans = INT_MAX;
        for (int i = 0; i <= 3; ++i) {
            ans = min(ans, nums[n - 1 - (3 - i)] - nums[i]);
        }
        return ans;
    }
};
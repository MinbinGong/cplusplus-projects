/*
 * Delete and Earn
 *
 * Given an array nums of integers, you can perform operations on the array.
 * 
 * In each operation, you pick any nums[i] and delete it to earn nums[i] points. After, you must delete every element equal to nums[i] - 1 or nums[i] + 1.
 * 
 * You start with 0 points. Return the maximum number of points you can earn by applying such operations.
 * 
 * Note:
 * 1. The length of nums is at most 20000.
 * 2. Each element nums[i] is an integer in the range [1, 10000].
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        // Find the maximum value in nums to determine the range of sums
        int maxVal = *max_element(nums.begin(), nums.end());
        
        // sums[i] = total points we can get from all occurrences of value i
        vector<int> sums(maxVal + 1, 0);
        for (int num : nums) {
            sums[num] += num;
        }
        
        // Dynamic programming similar to House Robber:
        // For each value i, we can either skip it (take previous max) or take it
        // and add its sum to the max we had two steps before.
        int take = 0;  // max points considering up to previous value (i-1) including i-1
        int skip = 0;  // max points considering up to previous value (i-1) but not including i-1 (actually skip is previous take? Let's use two variables correctly)
        // Actually we need two variables: prevTake (max up to i-1) and prevSkip (max up to i-2)? Simpler: use two variables: prev and prevPrev.
        int prev = 0;   // dp[i-1]
        int prevPrev = 0; // dp[i-2]
        
        for (int i = 0; i <= maxVal; ++i) {
            int curr = max(prev, prevPrev + sums[i]);
            prevPrev = prev;
            prev = curr;
        }
        
        return prev;
    }
};
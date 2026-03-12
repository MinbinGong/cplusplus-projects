/**
 * 1755. Closest Subsequence Sum
 * 
 * You are given an integer array nums and an integer goal.
 * 
 * You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal.
 * That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).
 * 
 * Return the minimum possible value of abs(sum - goal).
 * 
 * Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.
 * 
 * Example 1:
 * 
 * Input: nums = [5,-7,3,5], goal = 6
 * Output: 0
 * Explanation: Choose the whole array as a subsequence, with a sum of 6.
 * 
 * Example 2:
 * 
 * Input: nums = [7,-9,15,-2], goal = -5
 * Output: 1
 * Explanation: Choose the subsequence [7,-9,-2], with a sum of -4.
 * 
 * Example 3:
 * 
 * Input: nums = [1,2,3], goal = -7
 * Output: 7
 * 
 * Constraints:
 * 
 * 1 <= nums.length <= 40
 * -10^7 <= nums[i] <= 10^7
 * -10^9 <= goal <= 10^9
 * 
 */

#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int minAbsDifference(std::vector<int>& nums, int goal) {
        int n = nums.size();
        int mid = n / 2;
        std::vector<int> left(nums.begin(), nums.begin() + mid);
        std::vector<int> right(nums.begin() + mid, nums.end());

        std::vector<long long> leftSums, rightSums;

        // all subset sums for left half
        int leftSize = left.size();
        for (int mask = 0; mask < (1 << leftSize); ++mask) {
            long long sum = 0;
            for (int i = 0; i < leftSize; ++i) {
                if (mask & (1 << i))
                    sum += left[i];
            }
            leftSums.push_back(sum);
        }

        // all subset sums for right half
        int rightSize = right.size();
        for (int mask = 0; mask < (1 << rightSize); ++mask) {
            long long sum = 0;
            for (int i = 0; i < rightSize; ++i) {
                if (mask & (1 << i))
                    sum += right[i];
            }
            rightSums.push_back(sum);
        }

        std::sort(rightSums.begin(), rightSums.end());

        long long best = LLONG_MAX;
        for (long long ls : leftSums) {
            long long target = (long long)goal - ls;
            auto it = std::lower_bound(rightSums.begin(), rightSums.end(), target);
            if (it != rightSums.end())
                best = std::min(best, std::abs(ls + *it - goal));
            if (it != rightSums.begin()) {
                --it;
                best = std::min(best, std::abs(ls + *it - goal));
            }
        }

        return (int)best;
    }
};
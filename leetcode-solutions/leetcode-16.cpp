/*
 * Given an integer array nums of length n and an integer target,
 * find three integers in nums such that the sum is closest to target.
 *
 * Return the sum of the three integers.
 *
 * You may assume that each input would have exactly one solution.
 */
#include <algorithm>
#include <vector>

int threeSumClosest(std::vector<int> &nums, int target) {
    std::sort(nums.begin(), nums.end());
    int prev = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < nums.size() - 1; i++) {
        int j = i + 1;
        int k = nums.size() - 1;
        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (abs(sum - target) < abs(prev - target)) {
                prev = sum;
            }

            if (sum < target) {
                j++;
            } else {
                k--;
            }
        }
    }
    return prev;
}
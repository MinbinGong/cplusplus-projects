/*
 * Maximum Average Subarray II
 *
 * Given an array consisting of n integers, find the contiguous subarray whose length is greater than or equal to k that has the maximum average value.
 * And you need to output the maximum average value.
 *
 * Note:
 *
 * 1 <= k <= n <= 10,000.
 * Elements of the given array will be in the range [-10,000, 10,000].
 *
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double left = *min_element(nums.begin(), nums.end());
        double right = *max_element(nums.begin(), nums.end());
        double eps = 1e-5;

        // 二分查找最大平均值
        while (right - left > eps) {
            double mid = left + (right - left) / 2;
            if (check(nums, k, mid)) {
                left = mid;      // 可以达到更高平均值
            } else {
                right = mid;     // 必须降低平均值
            }
        }
        return left;
    }

private:
    // 检查是否存在长度 ≥ k 且平均值 ≥ target 的子数组
    bool check(const vector<int>& nums, int k, double target) {
        double sum = 0;           // 当前前缀和（减去target后）
        double prevSum = 0;       // 之前的前缀和，用于计算窗口
        double minPrevSum = 0;     // 从开始到 i-k 的最小前缀和

        // 计算前 k 个元素的和
        for (int i = 0; i < k; ++i) {
            sum += nums[i] - target;
        }
        if (sum >= 0) return true;

        for (int i = k; i < nums.size(); ++i) {
            sum += nums[i] - target;              // 更新当前前缀和
            prevSum += nums[i - k] - target;       // 窗口左端移出的元素
            minPrevSum = min(minPrevSum, prevSum); // 维护最小前缀和

            if (sum >= minPrevSum) {
                return true;   // 找到了符合条件的子数组
            }
        }
        return false;
    }
};
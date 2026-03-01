/*
 * 1300. Sum of Mutated Array Closest to Target
 * 
 * Given an integer array arr and a target value target, return the integer value such that when we change all the integers larger than value in the given array to be equal to value, the sum of the array gets as close as possible (in absolute difference) to target.
 * 
 * In case of a tie, return the minimum such integer.
 * 
 * Notice that the answer is not neccesarilly a number from arr.
 * 
 * Example 1:
 * Input: arr = [4,9,3], target = 10
 * Output: 3
 * Explanation: 
 * When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.
 * 
 * Example 2:
 * Input: arr = [2,3,5], target = 10
 * Output: 5
 * 
 * Example 3:
 * Input: arr = [60864,25176,27249,21296,20204], target = 56803
 * Output: 11361
 * 
 * Note:
 * 1 <= arr.length <= 10^4
 * 1 <= arr[i], target <= 10^5
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        // 排序并计算前缀和
        sort(arr.begin(), arr.end());
        int n = arr.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + arr[i];
        }

        // 辅助函数：计算以 value 为阈值时的数组和
        auto getSum = [&](int val) -> int {
            // 找到第一个大于 val 的位置
            auto it = upper_bound(arr.begin(), arr.end(), val);
            int idx = it - arr.begin();  // 小于等于 val 的元素个数
            return prefix[idx] + (n - idx) * val;
        };

        // 二分查找第一个使得和 >= target 的 value
        int left = 0, right = arr.back();
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (getSum(mid) >= target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        // 两个候选：left 和 left-1
        int cand1 = left;
        int cand2 = left - 1;

        int sum1 = getSum(cand1);
        int diff1 = abs(sum1 - target);

        // cand2 可能为 -1，此时不考虑
        int diff2 = INT_MAX;
        if (cand2 >= 0) {
            int sum2 = getSum(cand2);
            diff2 = abs(sum2 - target);
        }

        if (diff1 < diff2) return cand1;
        if (diff1 > diff2) return cand2;
        return min(cand1, cand2);  // 相等时取较小值
    }
};
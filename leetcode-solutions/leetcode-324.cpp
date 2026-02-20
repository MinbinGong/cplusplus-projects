/*
 * Wiggle Sort II
 * 
 * Given an integer array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
 * You may assume the input array always has a valid answer.
 * 
 * Example 1:
 * Input: nums = [1,5,1,1,6,4]
 * Output: [1,6,1,5,1,4]
 * Explanation: [1,4,1,5,1,6] is also accepted.
 * 
 * Example 2:
 * Input: nums = [1,3,2,2,3,1]
 * Output: [2,3,1,3,1,2]
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return;

        // 1. 找到中位数 (第 n/2 小的元素)
        auto mid = nums.begin() + n / 2;
        nth_element(nums.begin(), mid, nums.end());
        int median = *mid;

        // 2. 三路划分 (荷兰国旗) : 小于、等于、大于 median
        int i = 0, j = 0, k = n - 1;
        while (j <= k) {
            if (nums[j] < median) {
                swap(nums[i], nums[j]);
                ++i; ++j;
            } else if (nums[j] > median) {
                swap(nums[j], nums[k]);
                --k;
            } else {
                ++j;
            }
        }
        // 此时 nums[0..i-1] < median, nums[i..k] = median, nums[k+1..n-1] > median

        // 3. 将数组分成两个半区: 前一半为较小的一半，后一半为较大的一半
        //    注意 half = (n+1)/2 确保奇数时前半区多一个元素
        int half = (n + 1) / 2;
        vector<int> temp = nums;        // 拷贝一份（此时已分组）

        // 4. 反向交错填充: 偶数下标放入前半区的元素（从后往前），奇数下标放入后半区的元素（从后往前）
        //    这样可以避免相邻元素相等
        int left = half - 1;             // 前半区最后一个索引
        int right = n - 1;                // 后半区最后一个索引
        for (int idx = 0; idx < n; ++idx) {
            if (idx % 2 == 0) {
                nums[idx] = temp[left--];
            } else {
                nums[idx] = temp[right--];
            }
        }
    }
};
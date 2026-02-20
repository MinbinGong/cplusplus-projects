/*
 * Create Maximum Number
 * 
 * You are given two integer arrays nums1 and nums2 of lengths m and n respectively.
 * nums1 and nums2 represent the digits of two numbers. You are also given an integer k.
 * Create the maximum number of length k <= m + n from digits of the two numbers.
 * The relative order of the digits from the same array must be preserved.
 * Return an array of the k digits representing the answer.
 * 
 * Example 1:
 * Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
 * Output: [9,8,6,5,3]
 * 
 * Example 2:
 * Input: nums1 = [6,7], nums2 = [6,0,4], k = 5
 * Output: [6,7,6,0,4]
 * 
 * Example 3:
 * Input: nums1 = [3,9], nums2 = [8,9], k = 3
 * Output: [9,8,9]
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(), n = nums2.size();
        vector<int> result;
        // 枚举从 nums1 中取 i 个数字，则从 nums2 中取 k - i 个数字
        for (int i = max(0, k - n); i <= min(k, m); ++i) {
            vector<int> sub1 = maxSubsequence(nums1, i);
            vector<int> sub2 = maxSubsequence(nums2, k - i);
            vector<int> merged = merge(sub1, sub2);
            if (greater(merged, 0, result, 0)) {
                result.swap(merged);
            }
        }
        return result;
    }

private:
    // 从一个数组中按顺序选出 k 个数字，使得组成的数最大（单调栈）
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        if (k == 0) return {};
        vector<int> res;
        int n = nums.size();
        int remain = n - k; // 可以删除的数字个数
        for (int num : nums) {
            while (!res.empty() && res.back() < num && remain > 0) {
                res.pop_back();
                --remain;
            }
            res.push_back(num);
        }
        // 如果有多余的，截取前 k 个
        res.resize(k);
        return res;
    }

    // 合并两个子序列，使得数字最大（类似归并，但要比较后面）
    vector<int> merge(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if (m == 0) return nums2;
        if (n == 0) return nums1;
        vector<int> merged(m + n);
        int i = 0, j = 0, idx = 0;
        while (i < m && j < n) {
            if (greater(nums1, i, nums2, j)) {
                merged[idx++] = nums1[i++];
            } else {
                merged[idx++] = nums2[j++];
            }
        }
        while (i < m) merged[idx++] = nums1[i++];
        while (j < n) merged[idx++] = nums2[j++];
        return merged;
    }

    // 比较两个数组从指定位置开始的字典序（即哪个更大）
    bool greater(vector<int>& nums1, int i, vector<int>& nums2, int j) {
        while (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j]) {
            ++i;
            ++j;
        }
        if (j == nums2.size()) return true;        // nums1 更长或相等，则 nums1 大
        if (i == nums1.size()) return false;       // nums2 更长
        return nums1[i] > nums2[j];                 // 比较第一个不同元素
    }
};
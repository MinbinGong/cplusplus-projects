/*
 * 1713. Minimum Operations to Make a Subsequence
 * 
 * You are given an array target that consists of distinct integers and another integer array arr that can have duplicates.
 * 
 * In one operation, you can insert any integer at any position in arr. For example, if arr = [1,4,1,2], you can add 3 in the middle and make it [1,4,3,1,2]. Note that you can insert the integer at the very beginning or end of the array.
 * 
 * Return the minimum number of operations needed to make target a subsequence of arr.
 * 
 * A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.
 * 
 * Example 1:
 * Input: target = [5,1,3], arr = [9,4,2,3,4]
 * Output: 2
 * Explanation: You can add 5 and 1 in such a way that makes arr = [5,9,4,1,2,3,4], then target will be a subsequence of arr.
 * 
 * Example 2:
 * Input: target = [6,4,8,1,3,2], arr = [4,7,6,2,3,8,6,1]
 * Output: 3
 * 
 * Constraints:
 * 1 <= target.length, arr.length <= 10^5
 * 1 <= target[i], arr[i] <= 10^9
 * target contains no duplicates.
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        // 记录 target 中每个元素的位置（target 元素互异）
        unordered_map<int, int> pos;
        for (int i = 0; i < target.size(); ++i) {
            pos[target[i]] = i;
        }

        // 提取 arr 中在 target 中出现的元素，并转换为 target 中的下标
        vector<int> indices;
        for (int x : arr) {
            if (pos.count(x)) {
                indices.push_back(pos[x]);
            }
        }

        // 对 indices 求最长递增子序列（LIS）的长度
        vector<int> lis;
        for (int idx : indices) {
            auto it = lower_bound(lis.begin(), lis.end(), idx);
            if (it == lis.end()) {
                lis.push_back(idx);
            } else {
                *it = idx;
            }
        }

        // 最少操作次数 = target 长度 - 最长公共子序列长度（即最长匹配的序列长度）
        return target.size() - lis.size();
    }
};
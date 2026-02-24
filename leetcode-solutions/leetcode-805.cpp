/*
 * 805. Split Array With Same Average
 * 
 * In a given integer array A, we must move every element of A to either list B or list C. (B and C initially start empty.)
 * 
 * Return true if and only if after such a move, it is possible that the average value of B is equal to the average value of C, and B and C are both non-empty.
 * 
 * Example :
 * Input: 
 * [1,2,3,4,5,6,7,8]
 * Output: true
 * Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have the average of 4.5.
 * 
 * Note:
 * The length of A will be in the range [1, 30].
 * A[i] will be in the range of [0, 10000].
 * 
 */
#include <vector>
#include <numeric>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return false; // 单个元素无法分割成两个非空数组

        int sum = accumulate(nums.begin(), nums.end(), 0);

        // 步骤1：对数组进行归一化处理
        vector<int> A(n);
        for (int i = 0; i < n; ++i) {
            A[i] = nums[i] * n - sum;
        }

        // 步骤2：折半搜索
        int m = n / 2; // 左半部分的长度
        unordered_set<int> leftSums; // 存储左半部分所有可能的子集和

        // 枚举左半部分 (前m个元素) 的所有子集和
        // 从1开始，排除空集。这里左半部分的子集对应着整个数组的子集
        for (int i = 1; i < (1 << m); ++i) {
            int total = 0;
            for (int j = 0; j < m; ++j) {
                if (i & (1 << j)) {
                    total += A[j];
                }
            }
            if (total == 0) return true; // 找到一个和为0的子集
            leftSums.insert(total);
        }

        // 枚举右半部分 (剩余元素) 的所有子集和
        int r = n - m; // 右半部分的长度
        for (int i = 1; i < (1 << r); ++i) {
            int total = 0;
            for (int j = 0; j < r; ++j) {
                if (i & (1 << j)) {
                    total += A[m + j];
                }
            }
            if (total == 0) return true; // 找到一个和为0的子集

            // 关键步骤：检查是否存在一个左半部分的子集和，与当前total互为相反数
            // 条件 `i != (1 << r) - 1` 是为了确保右半部分没选全部元素。
            // 因为如果左右都选全部，那最终子集就是整个数组，不符合要求（非全体）。
            // 结合左半部分从1开始（排除了空集），这个条件共同保证了子集非空且非全体。
            if (i != (1 << r) - 1 && leftSums.count(-total)) {
                return true;
            }
        }

        return false;
    }
};
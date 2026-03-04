/*
 * 1569. Number of Ways to Reorder Array to Get Same BST
 * 
 * Given an array nums that represents a permutation of integers from 1 to n. We are going to construct a binary search tree (BST) by inserting the elements of nums in order into an initially empty BST. Find the number of different ways to reorder nums so that the constructed BST is identical to that formed from the original array nums.
 * 
 * For example, given nums = [2,1,3], we will have 2 as the root, 1 as a left child, and 3 as a right child. The array [2,3,1] also yields the same BST but [3,2,1] yields a different BST.
 * 
 * Return the number of ways to reorder nums such that the BST formed is identical to the original BST formed from nums.
 * 
 * Since the answer may be very large, return it modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: nums = [2,1,3]
 * Output: 1
 * Explanation: We can reorder nums to be [2,3,1] which will yield the same BST. There are no other ways to reorder nums which will yield the same BST.
 * 
 * Example 2:
 * Input: nums = [3,4,5,1,2]
 * Output: 5
 * Explanation: The following 5 arrays will yield the same BST: 
 * [3,1,2,4,5]
 * [3,1,4,2,5]
 * [3,1,4,5,2]
 * [3,4,1,2,5]
 * [3,4,1,5,2]
 * 
 * Constraints:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= nums.length
 * All integers in nums are distinct.
 * 
 */
#include <vector>
using namespace std;

class Solution {
private:
    static const int MOD = 1e9 + 7;
    vector<vector<long long>> comb; // 存储组合数 C[i][j]

    // 预计算组合数，使用杨辉三角
    void initComb(int n) {
        comb.resize(n + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= n; ++i) {
            comb[i][0] = comb[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
            }
        }
    }

    // 递归计算方案数
    long long dfs(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 1; // 空树或单节点树只有一种方案

        int root = nums[0];
        vector<int> left, right;
        // 划分左右子树，保持原顺序
        for (int i = 1; i < n; ++i) {
            if (nums[i] < root) left.push_back(nums[i]);
            else right.push_back(nums[i]);
        }

        int l = left.size(), r = right.size();
        // 组合数 C(l + r, l) * 左子树方案 * 右子树方案
        long long ans = comb[l + r][l];
        ans = ans * dfs(left) % MOD;
        ans = ans * dfs(right) % MOD;
        return ans;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        initComb(n); // 预计算组合数
        // 减 1 并处理负数取模
        return (dfs(nums) - 1 + MOD) % MOD;
    }
};

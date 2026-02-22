/*
 * Equal Tree Partition
 *
 * Given a binary tree with n nodes, your task is to check if it's possible to partition the tree to two trees which have the equal sum of values after removing exactly one edge on the original tree.
 *
 * Example 1:
 *
 * Input:     
 *           5
 *          / \
 *         10 10
 *           /  \
 *          2   3
 *
 * Output: True
 * Explanation:
 *           5
 *          / 
 *        10
 *       
 * Sum: 15
 *
 *          10
 *         /  \
 *        2    3
 *
 * Sum: 15
 *
 * Example 2:
 *
 * Input:     
 *           1
 *          / \
 *         2  10
 *           /  \
 *          2   20
 *
 * Output: False
 * Explanation: You can't split the tree into two trees with equal sum after removing exactly one edge on the tree.
 *
 * Note:
 *
 * The number of nodes in the given tree is between [1, 10^4].
 * Each node's value is between [-10^5, 10^5].
 * 
 */
#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool checkEqualTree(TreeNode* root) {
        vector<int> subtreeSums;                // 存储所有子树的和
        int total = getSum(root, subtreeSums);  // 计算总和并收集子树和

        // 总和为奇数，无法平分
        if (total % 2 != 0) return false;

        // 移除整棵树自身的和（即最后一个元素）
        subtreeSums.pop_back();

        // 查找是否存在子树和为 total/2
        int target = total / 2;
        for (int sum : subtreeSums) {
            if (sum == target) return true;
        }
        return false;
    }

private:
    // 后序遍历计算子树和，并将每个子树的和加入容器
    int getSum(TreeNode* node, vector<int>& sums) {
        if (!node) return 0;
        int leftSum = getSum(node->left, sums);
        int rightSum = getSum(node->right, sums);
        int curSum = leftSum + rightSum + node->val;
        sums.push_back(curSum);
        return curSum;
    }
};
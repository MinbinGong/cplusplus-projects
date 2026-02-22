/*
 * Second Minimum Node In a Binary Tree
 *
 * Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree
 * has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among
 * its two sub-nodes.
 *
 * Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the
 * whole tree.
 *
 * If no such second minimum value exists, output -1 instead.
 *
 * Example 1:
 *
 * Input:
 *     2
 *    / \
 *   2   5
 *      / \
 *     5   7
 *
 * Output: 5
 * Explanation: The smallest value is 2, the second smallest value is 5.
 *
 * Example 2:
 *
 * Input:
 *     2
 *    / \
 *   2   2
 *
 * Output: -1
 * Explanation: The smallest value is 2, but there isn't any second smallest value.
 *
 * Note:
 *
 * The number of nodes in the given tree will be at most 10000.
 * Each node's value is an integer in the range [0, 10^9].
 *
 */
#include <climits>
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
  int findSecondMinimumValue(TreeNode *root) {
    if (!root) return -1;
    long long secondMin = LONG_MAX;  // use long to handle cases where val can be INT_MAX
    dfs(root, root->val, secondMin);
    return secondMin == LONG_MAX ? -1 : secondMin;
  }

 private:
  void dfs(TreeNode *node, int rootVal, long long &secondMin) {
    if (!node) return;
    // If current node's value is greater than root and smaller than current second minimum
    if (node->val > rootVal && node->val < secondMin) {
      secondMin = node->val;
    }
    // Recurse left and right
    dfs(node->left, rootVal, secondMin);
    dfs(node->right, rootVal, secondMin);
  }
};
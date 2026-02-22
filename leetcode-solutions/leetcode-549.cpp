/*
 * Binary Tree Longest Consecutive Sequence II
 *
 * Given a binary tree, you need to find the length of Longest Consecutive Path in Binary Tree.
 *
 * Especially, this path can be either increasing or decreasing. For example, [1,2,3,4] and [4,3,2,1] are both
 * considered valid, but the path [1,2,4,3] is not valid. On the other hand, the path can be in the child-Parent-child
 * order, where not necessarily be parent-child order.
 *
 * Note:
 * The length of path between two nodes is represented by the number of edges between them.
 *
 */
#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
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
  int longestConsecutive(TreeNode *root) {
    int ans = 0;
    dfs(root, ans);
    return ans;
  }

 private:
  // 返回值是一个 pair<int, int>，first 是 inc，second 是 dec
  pair<int, int> dfs(TreeNode *node, int &ans) {
    if (!node) return {0, 0};

    int inc = 1;  // 至少包含当前节点自己
    int dec = 1;

    auto [left_inc, left_dec] = dfs(node->left, ans);
    auto [right_inc, right_dec] = dfs(node->right, ans);

    // 处理左子节点
    if (node->left) {
      if (node->left->val + 1 == node->val) {
        inc = max(inc, left_inc + 1);
      }
      if (node->left->val - 1 == node->val) {
        dec = max(dec, left_dec + 1);
      }
    }

    // 处理右子节点
    if (node->right) {
      if (node->right->val + 1 == node->val) {
        inc = max(inc, right_inc + 1);
      }
      if (node->right->val - 1 == node->val) {
        dec = max(dec, right_dec + 1);
      }
    }

    // 更新全局最大值：经过当前节点的最长路径
    ans = max(ans, inc + dec - 1);

    return {inc, dec};
  }
};
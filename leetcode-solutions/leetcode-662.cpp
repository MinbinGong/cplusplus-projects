/*
 * Maximum Width of Binary Tree
 *
 * Given a binary tree, write a function to get the maximum width of the given tree. The width of a tree is the maximum
 * width among all levels. The binary tree has the same structure as a full binary tree, but some nodes are null.
 *
 * The width of one level is defined as the length between the end-nodes (the leftmost and right most non-null nodes in
 * the level, where the null nodes between the end-nodes are also counted into the length calculation.
 *
 * Example 1:
 *
 * Input:
 *
 *            1
 *          /   \
 *         3     2
 *        / \     \
 *       5   3     9
 *
 * Output: 4
 * Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
 *
 * Example 2:
 *
 * Input:
 *
 *           1
 *          /
 *         3
 *        / \
 *       5   3
 *
 * Output: 2
 * Explanation: The maximum width existing in the third level with the length 2 (5,3).
 *
 * Note:
 *
 * The given binary tree will have between 1 and 3000 nodes.
 *
 */
#include <queue>
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
  int widthOfBinaryTree(TreeNode *root) {
    if (!root) return 0;
    queue<pair<TreeNode *, unsigned long long>> q;
    q.push({root, 0});
    unsigned long long maxWidth = 0;

    while (!q.empty()) {
      int levelSize = q.size();
      unsigned long long left = q.front().second;
      unsigned long long right = left;

      for (int i = 0; i < levelSize; ++i) {
        auto [node, idx] = q.front();
        q.pop();
        right = idx;  // keep updating to the last node's index

        if (node->left) q.push({node->left, 2 * idx});
        if (node->right) q.push({node->right, 2 * idx + 1});
      }

      unsigned long long width = right - left + 1;
      if (width > maxWidth) maxWidth = width;
    }

    return static_cast<int>(maxWidth);
  }
};
/**
 * Longest Common Subsequence
 *
 * Given two strings text1 and text2, return the length of their longest common subsequence.
 * If there is no common subsequence, return 0.
 *
 * A subsequence of a string is a new string generated from the original string with some characters (can be none)
 * deleted without changing the relative order of the remaining characters.
 *
 * For example, "ace" is a subsequence of "abcde".
 * A common subsequence of two strings is a subsequence that is common to both strings.
 *
 * 1 <= text1.length, text2.length <= 1000
 * text1 and text2 consist of only lowercase English characters.
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
  TreeNode *lcaDeepestLeaves(TreeNode *root) { return dfs(root).second; }

 private:
  // Returns a pair {depth, LCA node} for the subtree rooted at 'node'.
  // Depth is the number of edges from 'node' to its deepest leaf.
  pair<int, TreeNode *> dfs(TreeNode *node) {
    if (!node) return {-1, nullptr};  // null subtree: depth -1

    auto left = dfs(node->left);
    auto right = dfs(node->right);

    if (left.first > right.first) {
      // Deepest leaves are only in left subtree
      return {left.first + 1, left.second};
    }
    if (right.first > left.first) {
      // Deepest leaves are only in right subtree
      return {right.first + 1, right.second};
    }
    // Both sides have deepest leaves at equal depth
    return {left.first + 1, node};
  }
};
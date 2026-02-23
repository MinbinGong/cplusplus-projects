/*
 * Longest Univalue Path
 *
 * Given a binary tree, find the length of the longest path where each node in the path has the same value. This path
 * may or may not pass through the root.
 *
 * Note: The length of path between two nodes is represented by the number of edges between them.
 *
 * Example 1:
 *
 * Input:
 *
 *               5
 *              / \
 *             4   5
 *            / \   \
 *           1   1   5
 *
 * Output:
 *
 * 2
 *
 * Example 2:
 *
 * Input:
 *
 *               1
 *              / \
 *             4   5
 *            / \   \
 *           4   4   5
 *
 * Output:
 *
 * 2
 *
 * Note:
 *
 * The given binary tree has not more than 10000 nodes. The height of the tree is not more than 1000.
 *
 * Constraints:
 *
 * The number of nodes in the tree is in the range [0, 104].
 * -1000 <= Node.val <= 1000
 * The depth of the tree will not exceed 1000.
 *
 */
#include <algorithm>
#include <numeric>
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
  int longestUnivaluePath(TreeNode *root) {
    int ans = 0;
    dfs(root, ans);
    return ans;
  }

 private:
  // 返回以当前节点为起点的最长同值路径长度（边数）
  int dfs(TreeNode *node, int &ans) {
    if (!node) return 0;

    int left = dfs(node->left, ans);
    int right = dfs(node->right, ans);

    int leftPath = 0, rightPath = 0;
    if (node->left && node->left->val == node->val) {
      leftPath = left + 1;
    }
    if (node->right && node->right->val == node->val) {
      rightPath = right + 1;
    }

    // 更新全局最大值：经过当前节点的路径长度
    ans = max(ans, leftPath + rightPath);

    // 返回给父节点的是单侧最长路径
    return max(leftPath, rightPath);
  }
};
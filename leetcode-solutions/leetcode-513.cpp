/*
 * @lc app=leetcode.cn id=617 lang=cpp
 *
 * Find Bottom Left Tree Value
 *
 * Given the root of a binary tree, return the leftmost value in the last row of the tree.
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 104].
 * -231 <= Node.val <= 231 - 1
 * 
 */

int findBottomLeftValue(TreeNode* root) {
  int ans = 0;
  if (root == nullptr) return ans;
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    int size = q.size();
    for (int i = 0; i < size; ++i) {
      TreeNode* node = q.front();
      q.pop();
      if (i == 0) ans = node->val;
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
    }
  }
  return ans;
}
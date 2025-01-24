/*
 * @lc app=leetcode.cn id=617 lang=cpp
 *
 * Find Bottom Left Tree Value
 *
 * 题目描述
 *     给定一个二叉树，在树的最后一行找到最左边的值。
 *
 * 题解：
 *     利用广度优先搜索，对每一层的节点进行遍历，然后取最后一层的第一个节点的值。
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
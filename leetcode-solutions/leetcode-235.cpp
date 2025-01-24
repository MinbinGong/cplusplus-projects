/*
 * Lowest Common Ancestor of a Binary Tree
 * 题目描述
 *     给定一个二叉树，找到该树中两个指定节点的最近公共祖先。
 *     最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x
 * 的深度尽可能大（一个节点也可以是它自己 的祖先）。”
 *
 * 题解：
 *     利用深度优先搜索，对每一个节点进行遍历，然后判断该节点是否为 p 或 q，如果是，则返回该节点，否则返回 NULL。
 */

// TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//     if (root == nullptr) return nullptr;
//     if (root == p || root == q) return root;
//     TreeNode *left = lowestCommonAncestor(root->left, p, q);
//     TreeNode *right = lowestCommonAncestor(root->right, p, q);
//     if (left && right) return root; // p 和 q 分别在左右子树中
//     return left ? left : right; // p 和 q 都在左子树或右子树中
// }

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
  TreeNode *cur = root;
  while (true) {
    if (p->val < cur->val && q->val < cur->val) {
      cur = cur->left;
    } else if (p->val > cur->val && q->val > cur->val) {
      cur = cur->right;
    } else {
      break;
    }
  }
  return cur;
}
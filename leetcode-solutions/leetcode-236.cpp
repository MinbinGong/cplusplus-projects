/*
 * Lowest Common Ancestor of a Binary Tree
 *
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 *
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as
 * the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”
 *
 * Constraints:
 * 1. The number of nodes in the tree is in the range [2, 105].
 * 2. -109 <= Node.val <= 109
 * 3. All Node.val are unique.
 * 4. p and q will exist in the tree.
 * 5. p != q
 */
// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Base case: if root is null or root is one of the targets, return root
    if (!root || root == p || root == q) return root;

    // Search in left and right subtrees
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    // If both sides returned a node, current node is LCA
    if (left && right) return root;

    // Otherwise, return the non‑null side (or null if both null)
    return left ? left : right;
  }
};
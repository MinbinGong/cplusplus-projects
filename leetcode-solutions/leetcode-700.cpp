/*
 * Search in a Binary Search Tree
 *
 * Given the root node of a binary search tree (BST) and a value. You need to find the node in the BST that the node's
 * value equals the given value. Return the subtree rooted with that node. If such node doesn't exist, you should return
 * NULL.
 *
 * For example,
 *
 * Given the tree:
 *         4
 *        / \
 *       2   7
 *      / \
 *     1   3
 *
 * And the value to search: 2
 * You should return this subtree:
 *
 *       2
 *      / \
 *     1   3
 * In the example above, if we want to search the value 5, since there is no node with value 5, we should return NULL.
 *
 * Note that an empty tree is represented by NULL, therefore you would see the expected output (serialized tree format)
 * as [], not null.
 *
 * Example 1:
 *
 * Input: root = [4,2,7,1,3], val = 2
 * Output: [2,1,3]
 *
 * Example 2:
 *
 * Input: root = [4,2,7,1,3], val = 5
 * Output: []
 *
 * Note:
 * 1. The number of nodes in the tree is in the range [1, 5000].
 * 2. 1 <= Node.val <= 10^7.
 * 3. root is a binary search tree.
 * 4. 1 <= val <= 10^7.
 *
 */
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
  TreeNode *searchBST(TreeNode *root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    if (val < root->val)
      return searchBST(root->left, val);
    else
      return searchBST(root->right, val);
  }
};
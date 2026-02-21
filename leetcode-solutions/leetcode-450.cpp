/*
 * Delete Node in a BST
 *
 * Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
 *
 * Basically, the deletion can be divided into two stages:
 * Search for a node to remove.
 * If the node is found, delete the node.
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 104].
 * -105 <= Node.val <= 105
 * Each node has a unique value.
 * root is a valid binary search tree.
 * -105 <= key <= 105
 */
struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

TreeNode *deleteNode(TreeNode *root, int key) {
  if (root == nullptr) {
    return root;
  }

  if (root->val == key) {
    if (root->left == nullptr) {
      return root->right;
    }

    if (root->right == nullptr) {
      return root->left;
    }

    TreeNode *rightSmallest = root->right;
    while (rightSmallest->left) {
      rightSmallest = rightSmallest->left;
    }
    rightSmallest->left = root->left;
    return root->right;
  }

  if (root->val > key) {
    root->left = deleteNode(root->left, key);
  } else if (root->val < key) {
    root->right = deleteNode(root->right, key);
  }

  return root;
}

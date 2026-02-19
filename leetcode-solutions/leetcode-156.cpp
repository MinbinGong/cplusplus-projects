/*
 * binary tree upside down
 * Given the root of a binary tree, turn the tree upside down and return the new root.
 *
 * You can turn a binary tree upside down with the following steps:
 *
 * The original left child becomes the new root.
 * The original root becomes the new right child.
 * The original right child becomes the new left child.
 *
 * The mentioned steps are done level by level. It is guaranteed that every right node has a sibling (a left node with
 * the same parent) and has no children.
 */

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* upsideDownBinaryTree(TreeNode* root) {
  if (!root || !root->left) return root;  // base case: no left child

  TreeNode* newRoot = upsideDownBinaryTree(root->left);

  // Rewire: left child becomes new root's left/right assignments
  root->left->left = root->right;  // original right becomes new left leaf
  root->left->right = root;        // original root becomes new right child

  // Detach current node to avoid cycles
  root->left = nullptr;
  root->right = nullptr;

  return newRoot;
}

TreeNode* upsideDownBinaryTree2(TreeNode* root) {
  TreeNode *cur = root, *pre = nullptr, *next = nullptr, *preRight = nullptr;

  while (cur) {
    next = cur->left;       // save next left child
    cur->left = preRight;   // new left = previous node's right
    preRight = cur->right;  // save current right for next iteration
    cur->right = pre;       // new right = previous node

    pre = cur;  // move pointers forward
    cur = next;
  }
  return pre;  // new root (last node processed)
}
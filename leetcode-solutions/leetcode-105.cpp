/*
  Construct Binary Tree from Preorder and Inorder Traversal
  Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree
  and inorder is the inorder traversal of the same tree, construct and return the binary tree.
  Constraints:
  1. 1 <= preorder.length <= 3000
  2. inorder.length == preorder.length
  3. -3000 <= preorder[i], inorder[i] <= 3000
  4. preorder and inorder consist of unique values.
  5. Each value of inorder also appears in preorder.
  6. preorder is guaranteed to be the preorder traversal of the tree.
  7. inorder is guaranteed to be the inorder traversal of the tree.
 */
#include <unordered_map>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *buildHelper(unordered_map<int, int> &hash, vector<int> &preorder, int s0, int e0, int s1) {
  if (s0 > e0) {
    return nullptr;
  }
  int mid = preorder[s1], index = hash[mid], leftLen = index - s0 - 1;
  TreeNode *node = new TreeNode(mid);
  node->left = buildHelper(hash, preorder, s0, index - 1, s1 + 1);
  node->right = buildHelper(hash, preorder, index + 1, e0, s1 + 2 + leftLen);
  return node;
}

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
  if (preorder.empty()) {
    return nullptr;
  }
  unordered_map<int, int> hash;
  for (int i = 0; i < inorder.size(); ++i) {
    hash[inorder[i]] = i;
  }

  return buildHelper(hash, preorder, 0, preorder.size() - 1, 0);
}
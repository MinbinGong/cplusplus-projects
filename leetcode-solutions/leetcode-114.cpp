/*
 * Flatten Binary Tree to Linked List
 * Given the root of a binary tree, flatten the tree into a "linked list":
 * 1. The "linked list" should use the same TreeNode class
 *    where the right child pointer points to the next node in the list
 *    and the left child pointer is always null.
 * 2. The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 */
#include <vector>
using namespace std;

struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  explicit TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

void traversal(vector<int> &v, TreeNode *node) {
  if (node == nullptr) {
    return;
  }

  v.push_back(node->val);
  traversal(v, node->left);
  traversal(v, node->right);
}

void flatten(TreeNode *root) {
  vector<int> v;
  traversal(v, root);
  TreeNode *head = new TreeNode();
  TreeNode *cursor = head;
  for (int i = 0; i < v.size(); i++) {
    TreeNode *temp = new TreeNode(v[i]);
    cursor->right = temp;
    cursor = cursor->right;
  }

  cursor = head->right;
  TreeNode *cursor1 = root;

  while (cursor) {
    cursor1->val = cursor->val;
    cursor1->left = nullptr;
    cursor1->right = cursor->right;
    cursor = cursor->right;
    cursor1 = cursor1->right;
  }
}

void flatten1(TreeNode *root) {
  if (root == nullptr) {
    return;
  }

  TreeNode *cursor = root;
  while (cursor) {
    if (cursor->left) {
      TreeNode *temp = cursor->left;
      while (temp->right) {
        temp = temp->right;
      }
      temp->right = cursor->right;
      cursor->right = cursor->left;
      cursor->left = nullptr;
    }
    cursor = cursor->right;
  }
}
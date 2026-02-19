/*
 * Kth Smallest Element in a BST
 * Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values
 * of the nodes in the tree.
 *
 * Constraints:
 * 1. The number of nodes in the tree is n.
 * 2. 1 <= k <= n <= 104
 * 3. 0 <= Node.val <= 104
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <stack>
using namespace std;

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
  int kthSmallest(TreeNode *root, int k) {
    stack<TreeNode *> st;
    TreeNode *curr = root;

    while (curr || !st.empty()) {
      // Reach the leftmost node of the current subtree
      while (curr) {
        st.push(curr);
        curr = curr->left;
      }
      curr = st.top();
      st.pop();

      // Process current node
      if (--k == 0) return curr->val;

      // Move to the right subtree
      curr = curr->right;
    }

    return -1;  // k is invalid (should not happen)
  }
};
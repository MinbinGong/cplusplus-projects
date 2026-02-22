/*
 * 530. Minimum Absolute Difference in BST
 *
 * Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two
 * nodes.
 *
 * Example:
 * Input:
 *    1
 *     \
 *      3
 *     /
 *    2
 * Output:
 * 1
 * Explanation:
 * The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
 *
 * Note:
 * There are at least two nodes in this BST.
 * This question is the same as 783: https://leetcode.com/problems/minimum-distance-between-bst-nodes/
 *
 */
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

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

class Solution1 {
 public:
  int getMinimumDifference(TreeNode *root) {
    int minDiff = INT_MAX;
    int prev = -1;  // previous value
    stack<TreeNode *> st;
    TreeNode *curr = root;

    while (curr || !st.empty()) {
      // go to leftmost
      while (curr) {
        st.push(curr);
        curr = curr->left;
      }
      curr = st.top();
      st.pop();

      // process current node
      if (prev != -1) {
        minDiff = min(minDiff, curr->val - prev);
      }
      prev = curr->val;

      // move to right
      curr = curr->right;
    }
    return minDiff;
  }
};

class Solution2 {
public:
    int getMinimumDifference(TreeNode* root) {
        int minDiff = INT_MAX;
        int prev = -1;
        inorder(root, prev, minDiff);
        return minDiff;
    }
private:
    void inorder(TreeNode* node, int& prev, int& minDiff) {
        if (!node) return;
        inorder(node->left, prev, minDiff);
        if (prev != -1) {
            minDiff = min(minDiff, node->val - prev);
        }
        prev = node->val;
        inorder(node->right, prev, minDiff);
    }
};
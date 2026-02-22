/*
 * Construct String from Binary Tree
 *
 * You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing
 * way.
 *
 * The null node needs to be represented by empty parenthesis pair "()".
 * And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between
 * the string and the original binary tree.
 *
 * Example 1:
 * Input: Binary tree: [1,2,3,4]
 *        1
 *      /   \
 *     2     3
 *    /
 *   4
 * Output: "1(2(4))(3)"
 * Explanation: Originallay it needs to be "1(2(4)())(3()())",
 * but you need to omit all the unnecessary empty parenthesis pairs.
 * And it will be "1(2(4))(3)".
 *
 * Example 2:
 * Input: Binary tree: [1,2,3,null,4]
 *        1
 *      /   \
 *     2     3
 *      \
 *       4
 * Output: "1(2()(4))(3)"
 *
 * Note:
 * 1. The binary tree will have at most 1000 nodes.
 * 2. Each node's value will be between [1, 10^9].
 *
 */
#include <string>
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

class Solution {
 public:
  string tree2str(TreeNode *root) {
    if (!root) return "";

    string result = to_string(root->val);

    // Add left child (or empty parentheses if right exists)
    if (root->left || root->right) {
      result += "(" + tree2str(root->left) + ")";
    }

    // Add right child if present
    if (root->right) {
      result += "(" + tree2str(root->right) + ")";
    }

    return result;
  }
};
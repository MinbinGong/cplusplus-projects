/*
 * 655. Print Binary Tree
 *
 * Print a binary tree in an m*n 2D string array following these rules:
 *
 * The row number m should be equal to the height of the given binary tree.
 * The column number n should always be an odd number.
 * The root node's value (in string format) should be put in the exactly middle of the first row it can be put.
 * The column and the row where the root node belongs will separate the rest space into two parts (left-bottom part and
 * right-bottom part). You should print the left subtree in the left-bottom part and print the right subtree in the
 * right-bottom part. The left-bottom part and the right-bottom part should have the same size. Even if one subtree is
 * none while the other is not, you don't need to print anything for the none subtree but still need to leave the space
 * as large as that for the other subtree. However, if two subtrees are none, then you don't need to leave space for
 * both of them. Each unused space should contain an empty string "". Print the subtrees following the same rules.
 *
 * Example 1:
 *
 * Input:
 *      1
 *     /
 *    2
 * Output:
 * [["", "1", ""],
 *  ["2", "", ""]]
 *
 * Example 2:
 *
 * Input:
 *      1
 *     / \
 *    2   3
 *     \
 *      4
 * Output:
 * [["", "", "", "1", "", "", ""],
 *  ["", "2", "", "", "", "3", ""],
 *  ["", "", "4", "", "", "", ""]]
 *
 * Note:
 *
 * The height of binary tree is in the range of [1, 10].
 *
 */
#include <vector>
using namespace std;

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
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  vector<vector<string>> printTree(TreeNode* root) {
    int h = getHeight(root);  // height of the tree
    int rows = h;
    int cols = (1 << h) - 1;  // 2^h - 1
    vector<vector<string>> res(rows, vector<string>(cols, ""));
    fill(res, root, 0, 0, cols - 1);
    return res;
  }

 private:
  int getHeight(TreeNode* node) {
    if (!node) return 0;
    return 1 + max(getHeight(node->left), getHeight(node->right));
  }

  void fill(vector<vector<string>>& res, TreeNode* node, int row, int left, int right) {
    if (!node) return;
    int mid = left + (right - left) / 2;
    res[row][mid] = to_string(node->val);
    fill(res, node->left, row + 1, left, mid - 1);
    fill(res, node->right, row + 1, mid + 1, right);
  }
};
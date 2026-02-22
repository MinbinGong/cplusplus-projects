/*
 * Maximum Binary Tree
 *
 * Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:
 *
 * The root is the maximum number in the array.
 * The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
 * The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
 *
 * Construct the maximum tree by the given array and output the root node of this tree.
 *
 * Example 1:
 *
 * Input: [3,2,1,6,0,5]
 * Output: return the tree root node representing the following tree:
 *
 *       6
 *     /   \
 *    3     5
 *     \    /
 *      2  0
 *        \
 *         1
 *
 * Note:
 *
 * The size of the given array will be in the range [1,1000].
 *
 */
#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
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
  TreeNode* constructMaximumBinaryTree(vector<int>& nums) { return build(nums, 0, nums.size() - 1); }

 private:
  TreeNode* build(vector<int>& nums, int left, int right) {
    if (left > right) return nullptr;
    // find index of maximum element in current range
    int maxIdx = left;
    for (int i = left + 1; i <= right; ++i) {
      if (nums[i] > nums[maxIdx]) {
        maxIdx = i;
      }
    }
    TreeNode* root = new TreeNode(nums[maxIdx]);
    root->left = build(nums, left, maxIdx - 1);
    root->right = build(nums, maxIdx + 1, right);
    return root;
  }
};
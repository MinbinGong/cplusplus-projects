/*
 * Convert Sorted Array to Binary Search Tree
 * Given an integer array nums where the elements are sorted in ascending order,
 * convert it to a height-balanced binary search tree.
 *
 * Constraints:
 * 1. 1 <= nums.length <= 104
 * 2. -104 <= nums[i] <= 104
 * 3. nums is sorted in a strictly increasing order.
 */
#include <vector>
using namespace std;

struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  TreeNode(int x) : val(x) {}
  TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

TreeNode* sortedArrayToBST(vector<int>& nums) {
  if (nums.size() == 0) return nullptr;
  if (nums.size() == 1) return new TreeNode(nums[0]);

  int middle = nums.size() / 2;
  TreeNode *root = new TreeNode(nums[middle]);
  vector<int> leftSub(nums.begin(), nums.begin() + middle);
  vector<int> rightSub(nums.begin() + middle + 1, nums.end());
  root->left = sortedArrayToBST(leftSub);
  root->right = sortedArrayToBST(rightSub);
  return root;
}

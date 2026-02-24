/**
 * 889. Construct Binary Tree from Preorder and Postorder Traversal
 *
 * Return any binary tree that matches the given preorder and postorder traversals.
 * Values in the traversals pre and post are distinct positive integers.
 *
 * Example 1:
 * Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
 * Output: [1,2,3,4,5,6,7]
 *
 * Note:
 * 1 <= pre.length == post.length <= 30
 * pre[] and post[] are both permutations of 1, 2, ..., pre.length.
 * It is guaranteed an answer exists. If there exists multiple answers, you can return any of them.
 *
 */
#include <vector>
#include <unordered_map>
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
  TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
    int n = preorder.size();
    unordered_map<int, int> postMap;
    for (int i = 0; i < n; ++i) {
      postMap[postorder[i]] = i;
    }
    return build(preorder, 0, n - 1, postorder, 0, n - 1, postMap);
  }

 private:
  TreeNode* build(vector<int>& preorder, int preStart, int preEnd, vector<int>& postorder, int postStart, int postEnd,
                  unordered_map<int, int>& postMap) {
    if (preStart > preEnd) return nullptr;
    TreeNode* root = new TreeNode(preorder[preStart]);
    if (preStart == preEnd) return root;

    int leftRoot = preorder[preStart + 1];
    int leftRootIndex = postMap[leftRoot];
    int leftSize = leftRootIndex - postStart + 1;

    root->left = build(preorder, preStart + 1, preStart + leftSize, postorder, postStart, leftRootIndex, postMap);
    root->right = build(preorder, preStart + leftSize + 1, preEnd, postorder, leftRootIndex + 1, postEnd - 1, postMap);
    return root;
  }
};
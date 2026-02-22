/*
 * Find Duplicate Subtrees
 *
 * Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to return the
 * root node of any one of them.
 *
 * Two trees are duplicate if they have the same structure with same node values.
 *
 * Example 1:
 *
 *         1
 *        / \
 *       2   3
 *      /   / \
 *     4   2   4
 *        /
 *       4
 *
 * The following are two duplicate subtrees:
 *
 *       2
 *      /
 *     4
 *
 * and
 *
 *     4
 *
 * Therefore, you need to return above trees' root in the form of a list.
 *
 * Note:
 *
 * The number of the nodes in the tree will be in the range of [1, 10^4]
 *
 */
#include <vector>
#include <string>
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
  vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    unordered_map<string, int> count;  // serialized subtree -> frequency
    vector<TreeNode*> result;
    serialize(root, count, result);
    return result;
  }

 private:
  string serialize(TreeNode* node, unordered_map<string, int>& count, vector<TreeNode*>& result) {
    if (!node) return "#";  // null marker

    // recursively serialize left and right subtrees
    string left = serialize(node->left, count, result);
    string right = serialize(node->right, count, result);

    // build serialization for the current subtree
    // format: "val,left,right"
    string s = to_string(node->val) + "," + left + "," + right;

    // if this serialization appears exactly twice, we have found a duplicate subtree
    if (++count[s] == 2) {
      result.push_back(node);
    }

    return s;
  }
};
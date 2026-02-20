/*
 * Binary Tree Paths
 *
 * Given the root of a binary tree, return all root-to-leaf paths in any order.
 *
 * A leaf is a node with no children.
 *
 * Example 1:
 * Input: root = [1,2,3,null,5]
 * Output: ["1->2->5","1->3"]
 *
 * Example 2:
 * Input: root = [1]
 * Output: ["1"]
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 100].
 * -100 <= Node.val <= 100
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
#include <vector>
#include <string>
#include <stack>
#include <utility>
using namespace std;

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
  vector<string> binaryTreePaths(TreeNode *root) {
    vector<string> result;
    if (!root) return result;
    dfs(root, to_string(root->val), result);
    return result;
  }

 private:
  void dfs(TreeNode *node, string path, vector<string> &result) {
    // If leaf node, add the path to result
    if (!node->left && !node->right) {
      result.push_back(path);
      return;
    }

    if (node->left) {
      dfs(node->left, path + "->" + to_string(node->left->val), result);
    }
    if (node->right) {
      dfs(node->right, path + "->" + to_string(node->right->val), result);
    }
  }
};

class Solution2 {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        if (!root) return result;
        
        stack<pair<TreeNode*, string>> stk;
        stk.push({root, to_string(root->val)});
        
        while (!stk.empty()) {
            auto [node, path] = stk.top();
            stk.pop();
            
            if (!node->left && !node->right) {
                result.push_back(path);
            } else {
                if (node->right) {
                    stk.push({node->right, path + "->" + to_string(node->right->val)});
                }
                if (node->left) {
                    stk.push({node->left, path + "->" + to_string(node->left->val)});
                }
            }
        }
        return result;
    }
};
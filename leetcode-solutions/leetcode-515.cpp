/*
 * Find Largest Value in Each Tree Row
 *
 * Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).
 * 
 * Constraints:
 * The number of nodes in the tree will be in the range [0, 104].
 * -231 <= Node.val <= 231 - 1
 *
 */
#include <vector>
#include <queue>
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

class BFSSolution {
 public:
  vector<int> largestValues(TreeNode *root) {
    vector<int> result;
    if (!root) return result;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
      int levelSize = q.size();
      int levelMax = INT_MIN;

      for (int i = 0; i < levelSize; ++i) {
        TreeNode *node = q.front();
        q.pop();
        levelMax = max(levelMax, node->val);

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
      }
      result.push_back(levelMax);
    }
    return result;
  }
};

class DFSSolution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> result;
        dfs(root, 0, result);
        return result;
    }
    
private:
    void dfs(TreeNode* node, int depth, vector<int>& result) {
        if (!node) return;
        
        // If this is the first node at this depth, add its value.
        if (depth == result.size()) {
            result.push_back(node->val);
        } else {
            // Otherwise, update the maximum for this depth.
            result[depth] = max(result[depth], node->val);
        }
        
        dfs(node->left, depth + 1, result);
        dfs(node->right, depth + 1, result);
    }
};
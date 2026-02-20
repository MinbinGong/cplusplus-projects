/*
 * Closest Leaf in a Binary Tree
 *
 * Given the root of a binary tree where every node has a unique value and a target integer k,
 * return the value of the nearest leaf node to the target k in the tree.
 *
 * Nearest to a leaf means the least number of edges traveled on the binary tree to reach any leaf of the tree.
 * Also, a node is called a leaf if it has no children.
 *
 * Constraints:
 * 1. The number of nodes in the tree is in the range [1, 1000].
 * 2. 1 <= Node.val <= 1000
 * 3. All the values of the tree are unique.
 * 4. There exist some node in the tree where Node.val == k.
 * 5. 1 <= k <= 1000
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// 时间复杂度：O(n)
// 空间复杂度：O(n)
// 迭代算法
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
    int closestValue(TreeNode* root, double target) {
        int closest = root->val;
        TreeNode* node = root;
        
        while (node) {
            // Update closest if current node is closer
            if (abs(node->val - target) < abs(closest - target)) {
                closest = node->val;
            }
            // Decide direction
            if (target < node->val) {
                node = node->left;
            } else if (target > node->val) {
                node = node->right;
            } else {
                // Exact match
                break;
            }
        }
        return closest;
    }
};

class Solution2 {
 public:
  int closestValue(TreeNode *root, double target) {
    int closest = root->val;
    dfs(root, target, closest);
    return closest;
  }

 private:
  void dfs(TreeNode *node, double target, int &closest) {
    if (!node) return;

    if (abs(node->val - target) < abs(closest - target)) {
      closest = node->val;
    }

    if (target < node->val) {
      dfs(node->left, target, closest);
    } else if (target > node->val) {
      dfs(node->right, target, closest);
    } else {
      // exact match, no need to go further
      return;
    }
  }
};
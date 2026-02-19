/*
 * Count Complete Tree Nodes
 *
 * Given the root of a complete binary tree, return the number of the nodes in the tree.
 *
 * According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree,
 * and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last
 * level h.
 *
 * Constraints:
 * 1. The number of nodes in the tree is in the range [0, 5 * 104].
 * 2. 0 <= Node.val <= 5 * 104
 * 3. The tree is guaranteed to be complete.
 */

// Definition for a binary tree node.
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
  int countNodes(TreeNode *root) {
    if (!root) return 0;

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    if (leftHeight == rightHeight) {
      // left subtree is perfect: nodes = 2^leftHeight - 1
      return (1 << leftHeight) + countNodes(root->right);
    } else {
      // right subtree is perfect (height = leftHeight - 1)
      return (1 << rightHeight) + countNodes(root->left);
    }
  }

 private:
  int getHeight(TreeNode *node) {
    int h = 0;
    while (node) {
      h++;
      node = node->left;
    }
    return h;
  }
};

class Solution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        
        // Step 1: get height (number of levels) via leftmost path
        int h = 0;
        TreeNode* node = root;
        while (node) {
            h++;
            node = node->left;
        }
        // Number of nodes above last level = 2^(h-1) - 1
        int nodesAbove = (1 << (h - 1)) - 1;
        
        // Step 2: binary search on last level
        int left = 0, right = (1 << (h - 1)) - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (exists(root, h - 1, mid)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        // left is the first missing index, so last existing index = left - 1
        return nodesAbove + left;
    }
    
private:
    bool exists(TreeNode* root, int depth, int idx) {
        // path bits: for depth levels (excluding root), we have depth bits.
        // We start from the second level.
        TreeNode* node = root;
        int mask = 1 << (depth - 1); // highest bit for this depth
        while (node && mask > 0) {
            if (idx & mask) {
                node = node->right;
            } else {
                node = node->left;
            }
            mask >>= 1;
        }
        return node != nullptr;
    }
};
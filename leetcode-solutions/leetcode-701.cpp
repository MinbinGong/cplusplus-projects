/*
 * Insert into a Binary Search Tree
 *
 * Given the root node of a binary search tree (BST) and a value to be inserted into the tree, insert the value into the BST. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.
 * 
 * Note:
 * 1. There may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.
 * 2. 1 <= Node.val <= 10^7.
 * 3. root is a binary search tree.
 * 4. 1 <= val <= 10^7.
 * 5. val does not exist in the original BST.
 * 6. The number of nodes in the tree is in the range [1, 5000].
 * 
 */
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

class Solution1 {
public:
    // 递归解法
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);
        if (val < root->val)
            root->left = insertIntoBST(root->left, val);
        else
            root->right = insertIntoBST(root->right, val);
        return root;
    }
};

// 迭代解法
class Solution2 {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode* newNode = new TreeNode(val);
        if (!root) return newNode;
        
        TreeNode* cur = root;
        while (true) {
            if (val < cur->val) {
                if (cur->left) {
                    cur = cur->left;
                } else {
                    cur->left = newNode;
                    break;
                }
            } else {
                if (cur->right) {
                    cur = cur->right;
                } else {
                    cur->right = newNode;
                    break;
                }
            }
        }
        return root;
    }
};
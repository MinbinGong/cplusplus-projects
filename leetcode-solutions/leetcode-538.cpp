/*
 * Convert BST to Greater Tree
 *
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
 *
 * As a reminder, a binary search tree is a tree that satisfies these constraints:
 * 1. The left subtree of a node contains only nodes with keys less than the node's key.
 * 2. The right subtree of a node contains only nodes with keys greater than the node's key.
 * 3. Both the left and right subtrees must also be binary search trees.
 * 
 * Example 1:
 * Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
 * Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
 * 
 * Example 2:
 * Input: root = [0,null,1]
 * Output: [1,null,1]
 * 
 * Constraints:
 * 1. The number of nodes in the tree is in the range [0, 104].
 * 2. -104 <= Node.val <= 104
 * 3. All the values in the tree are unique.
 * 4. root is guaranteed to be a valid binary search tree.
 * 
 */
#include <vector>
#include <queue>

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left, *right;
    explicit TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {} 
};

int sum = 0;

void reverseInorder(TreeNode *root) {
    if (root == nullptr) return;
    reverseInorder(root->right);
    root->val += sum; 
    sum = root->val;
    reverseInorder(root->left);
}

TreeNode *convertBST(TreeNode* root) {
    reverseInorder(root);
    return root;
}

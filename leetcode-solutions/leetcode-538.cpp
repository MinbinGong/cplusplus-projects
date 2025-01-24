/*
 * Convert BST to Greater Tree
 * 题目描述
 *     给定一个二叉搜索树（Binary Search Tree），把它转换成为累加树（Greater Tree)，
 *     使得每个节点的值是原来的节点值加上所有大于它的节点值之和。
 * 
 * 题解：
 *     利用二叉搜索树的性质，右子树的节点值大于左子树的节点值，因此
 *     1. 先遍历右子树
 *     2. 再遍历左子树
 *     3. 最后遍历根节点
 *     这样就可以保证右子树的节点值大于左子树的节点值，然后累加即可。
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

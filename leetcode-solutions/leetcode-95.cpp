/*
 * Given an integer n, return all the structurally unique BST's (binary search trees),
 * which has exactly n nodes of unique values from 1 to n.
 * Return the answer in any order.
 */
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

TreeNode* clone(TreeNode *root) {
    if (root == nullptr)
        return root;

    TreeNode* newRoot = new TreeNode(root->val);
    newRoot->left = clone(root->left);
    newRoot->right = clone(root->right);
    return newRoot;
}

vector(TreeNode *> generateTrees(int n) {
        vector<TreeNode *> res(1, nullptr);
        for (int i = 1; i <= n; i++) {
            vector<TreeNode *> tmp;
            for (int j = 0; j < res.size(); j++) {
                

                


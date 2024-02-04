/*
 * Given the root of a binary tree, return the inorder traversal of its nodes' values.
 */
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

void inorder(TreeNode* root, vector<int> &ans) {
    if (root == nullptr)
        return;

    if (root->left != nullptr)
        inorder(root->left, ans);

    ans.push_back(root->val);

    if (root->right != nullptr)
        inorder(root->right, ans);
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    inorder(root, ans);
    return ans;
}

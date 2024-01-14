/*
Balanced binary tree
 */
#include <algorithm>
#include <cmath>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    explicit TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

int helper(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }

    int left = helper(root->left), right = helper(root->right);
    if (left == -1 || right == -1 || abs(left - right) > 1) {
        return -1;
    }
    return 1 + max(left, right);
}
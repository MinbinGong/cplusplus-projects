#include <climits>

struct TreeNode
{
    int val = 0;
    TreeNode *left = nullptr, *right = nullptr;
    TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

bool isValidBST(TreeNode *root, long long lower, long long upper)
{
    if (root == nullptr)
    {
        return true;
    }

    return root->val > lower && root->val < upper && isValidBST(root->left, lower, root->val) && isValidBST(root->right, root->val, upper);
}

bool isValidBST(TreeNode *root)
{
    return isValidBST(root, LONG_MIN, LONG_MAX);
}

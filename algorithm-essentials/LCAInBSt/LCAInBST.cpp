struct TreeNode
{
    int val = 0;
    TreeNode *left = nullptr, *right = nullptr;
    TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

TreeNode *lowestCommonAccestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == nullptr || p == nullptr || q == nullptr)
    {
        return nullptr;
    }

    if (p->val < root->val && q->val < root->val)
    {
        return lowestCommonAccestor(root->left, p, q);
    }

    if (p->val > root->val && q->val > root->val)
    {
        return lowestCommonAccestor(root->right, p, q);
    }

    return root;
}

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

TreeNode *deleteNode(TreeNode *root, int key)
{
    if (root == nullptr)
    {
        return root;
    }

    if (root->val == key)
    {
        if (root->left == nullptr)
        {
            return root->right;
        }

        if (root->right == nullptr)
        {
            return root->left;
        }

        TreeNode *rightSmallest = root->right;
        while (rightSmallest->left)
        {
            rightSmallest = rightSmallest->left;
        }
        rightSmallest->left = root->left;
        return root->right;
    }

    if (root->val > key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (root->val < key)
    {
        root->right = deleteNode(root->right, key);
    }

    return root;
}

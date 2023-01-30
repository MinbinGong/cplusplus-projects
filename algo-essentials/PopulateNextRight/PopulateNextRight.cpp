struct TreeLinkedNode
{
    int val = 0;
    TreeLinkedNode *left = nullptr, *right = nullptr, *next = nullptr;
    TreeLinkedNode(int x = 0, TreeLinkedNode *l = nullptr, TreeLinkedNode *r = nullptr, TreeLinkedNode *n = nullptr)
        : val(x), left(l), right(r), next(n) {}
};

void connect(TreeLinkedNode *root, TreeLinkedNode *sibling)
{
    if (root == nullptr)
    {
        return;
    }

    root->next = sibling;

    connect(root->left, root->right);

    if (sibling == nullptr)
    {
        connect(root->right, nullptr);
    }
    else
    {
        connect(root->right, sibling->left);
    }

    return;
}

void connect(TreeLinkedNode *root)
{
    connect(root, nullptr);
}

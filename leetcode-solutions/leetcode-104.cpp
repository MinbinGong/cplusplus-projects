/*
Maximum depth of binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left, *right;
    explicit TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

int maxDepth(TreeNode *root) { return root ? 1 + max(maxDepth(root->left), maxDepth(root->right)) : 0; }
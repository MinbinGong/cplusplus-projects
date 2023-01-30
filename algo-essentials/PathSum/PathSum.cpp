#include <vector>

struct TreeNode
{
    int val = 0;
    TreeNode *left = nullptr, *right = nullptr;
    TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

void pathSum(TreeNode *root, int gap, std::vector<int> &cur, std::vector<std::vector<int>> &result)
{
    if (root == nullptr)
    {
        return;
    }

    cur.push_back(root->val);

    if (root->left == nullptr && root->right == nullptr)
    {
        if (gap == root->val)
        {
            result.push_back(cur);
        }
    }

    pathSum(root->left, gap - root->val, cur, result);
    pathSum(root->right, gap - root->val, cur, result);

    cur.pop_back();

    return;
}

std::vector<std::vector<int>> pathSum(TreeNode *root, int sum)
{
    std::vector<std::vector<int>> result{};
    std::vector<int> cur;
    pathSum(root, sum, cur, result);
    return result;
}

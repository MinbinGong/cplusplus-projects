#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int solve(TreeNode *root, int sum, int target)
{
    if (root == nullptr)
    {
        return 0;
    }
    sum += root->val;
    int ans = 0;
    ans += (sum == target) ? 1 : 0;
    ans += solve(root->left, sum, target);
    ans += solve(root->right, sum, target);
    return ans;
}

int pathSum(TreeNode *root, int sum)
{
    if (root == nullptr)
    {
        return 0;
    }

    int ans = 0;
    ans += solve(root, 0, sum);
    ans += pathSum(root->left, sum);
    ans += pathSum(root->right, sum);
    return ans;
}
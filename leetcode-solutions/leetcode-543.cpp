/*
Diameter of Binary tree

题目描述
求一个二叉树的最长直径。直径的定义是二叉树上任意两节点之间的无向距离

题解
同样的，我们可以利用递归来处理树。解题时要注意，在我们处理某个子树时，我们更新的
最长直径值和递归返回的值是不同的。这是因为待更新的最长直径值是经过该子树根节点的最长
直径（即两侧长度）；而函数返回值是以该子树根节点为端点的最长直径值（即一侧长度），使用
这样的返回值才可以通过递归更新父节点的最长直径值）
 */
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    explicit TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

int helper(TreeNode *node, int &diameter) {
    if (node == nullptr) {
        return 0;
    }
    int l = helper(node->left, diameter), r = helper(node->right, diameter);
    diameter = max(l + r, diameter);
    return max(l, r) + 1;
}

int diameterOfBT(TreeNode *root) {
    int diameter = 0;
    helper(root, diameter);
    return diameter;
}
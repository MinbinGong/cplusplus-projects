/*
 * Subtree of Another Tree
 * 题目描述
 *     给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。
 *     s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看做它自身的一棵子树。
 *
 * 题解：
 *     先判断两棵树是否相等，再判断
 *     1. 左子树是否包含 t
 *     2. 右子树是否包含 t
 *     只要满足一个条件，就返回 true。
 *     终止条件：当 t 为 NULL 时，返回 true。当 s 为 NULL 时，返回 false。
 *     递归调用：当 t 不为 NULL 时，判断 s 和 t 是否相等，然后递归调用左右子树。
 *     递归返回：返回递归调用的结果。
 */

#include <vector>
#include <queue>

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left, *right;
    explicit TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};
bool isSubtree(TreeNode *s, TreeNode *t) {
    if (t == nullptr) return true;
    if (s == nullptr) return false;
    return isSameTree(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t); 
}

bool isSameTree(TreeNode *s, TreeNode *t) {
    if (s == nullptr && t == nullptr) return true;
    if (s == nullptr || t == nullptr) return false;
    return s->val == t->val && isSameTree(s->left, t->left) && isSameTree(s->right, t->right); 
}
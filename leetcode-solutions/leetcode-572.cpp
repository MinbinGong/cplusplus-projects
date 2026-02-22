/*
 * Subtree of Another Tree
 *
 * Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s.
 * A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.
 * 
 * Example:
 * Input:
 *      s = [3,4,5,1,2], t = [4,1,2]
 * Output: True
 * 
 * Input:
 *      s = [3,4,5,1,2,null,null,null,null,0]
 * Output: False
 * 
 * Note:
 * The number of nodes of the given tree s and t will be in the range [1, 2000].
 * The number of unique node values of s and t will be in the range [1, 10000].
 * 
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
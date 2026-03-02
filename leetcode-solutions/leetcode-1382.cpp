/**
 * 1382. Balance a Binary Search Tree
 * 
 * Given a binary search tree, return a balanced binary search tree with the same node values.
 * 
 * A binary search tree is balanced if and only if the depth of the two subtrees of every node never differ by more than 1.
 * 
 * If there is more than one answer, return any of them.
 * 
 * Example 1:
 * Input: root = [1,null,2,null,3,null,4,null,null]
 * Output: [2,1,3,null,null,null,4]
 * Explanation: This is not the only correct answer, [3,1,4,null,2,null,null] is also correct.
 * 
 * Example 2:
 * Input: root = [2,1,3]
 * Output: [2,1,3]
 * Explantion:
 * The tree is balanced as the depth of the two subtrees of every node never differ by more than 1.
 * 
 * Note:
 * The number of nodes in the tree is between 1 and 10^4.
 * The tree nodes will have distinct values between 1 and 10^5.
 * 
 */
#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> values;
        inorder(root, values);
        return buildBalanced(values, 0, values.size() - 1);
    }

private:
    void inorder(TreeNode* node, vector<int>& values) {
        if (!node) return;
        inorder(node->left, values);
        values.push_back(node->val);
        inorder(node->right, values);
    }

    TreeNode* buildBalanced(const vector<int>& values, int left, int right) {
        if (left > right) return nullptr;
        int mid = left + (right - left) / 2;
        TreeNode* node = new TreeNode(values[mid]);
        node->left = buildBalanced(values, left, mid - 1);
        node->right = buildBalanced(values, mid + 1, right);
        return node;
    }
};
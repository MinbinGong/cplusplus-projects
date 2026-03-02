/**
 * 1373. Maximum Sum BST in Binary Tree
 *
 * Given a binary tree root, the task is to return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).
 *
 * Assume a BST is defined as follows:
 *
 * The left subtree of a node contains only nodes with keys less than the node's key.
 * The right subtree of a node contains only nodes with keys greater than the node's key.
 * Both the left and right subtrees must also be binary search trees.
 * 
 * Example 1:
 * Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
 * Output: 20
 * Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.
 *
 * Example 2:
 * Input: root = [4,3,null,1,2]
 * Output: 2
 * Explanation: Maximum sum in a valid Binary search tree is obtained in a single root node with key equal to 2.
 * 
 * Example 3:
 * Input: root = [-4,-2,-5]
 * Output: 0
 * Explanation: All values are negatives. Return an empty BST.
 * 
 * Note:
 * Each tree has at most 40000 nodes..
 * Each node's value is between [-4 * 10^4 , 4 * 10^4].
 * 
 */
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxSumBST(TreeNode* root) {
        int ans = INT_MIN;
        dfs(root, ans);
        return ans;
    }

private:
    struct Info {
        int minVal;
        int maxVal;
        int sum;
        bool isBST;
    };

    Info dfs(TreeNode* node, int& ans) {
        if (!node) return {INT_MAX, INT_MIN, 0, true};

        Info left = dfs(node->left, ans);
        Info right = dfs(node->right, ans);

        // 判断以当前节点为根的子树是否为 BST
        if (left.isBST && right.isBST && left.maxVal < node->val && node->val < right.minVal) {
            int curSum = left.sum + right.sum + node->val;
            ans = max(ans, curSum);
            return {min(node->val, left.minVal), max(node->val, right.maxVal), curSum, true};
        } else {
            // 不是 BST，但仍返回实际的最小、最大值和总和
            return {min(node->val, min(left.minVal, right.minVal)),
                    max(node->val, max(left.maxVal, right.maxVal)),
                    left.sum + right.sum + node->val,
                    false};
        }
    }
};
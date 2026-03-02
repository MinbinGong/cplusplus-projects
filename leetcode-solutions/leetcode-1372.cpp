/**
 * 1372. Longest ZigZag Path in a Binary Tree
 *
 * Given a binary tree root, a ZigZag path for a binary tree is defined as follow:
 *
 * Choose any node in the binary tree and a direction (right or left).
 * If the current direction is right then move to the right child of the current node otherwise move to the left child.
 * Change the direction from right to left or right to left.
 * Repeat the second and third step until you can't move in the tree.
 * Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).
 *
 * Return the longest ZigZag path contained in that tree.
 *
 * Example 1:
 * Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1]
 * Output: 3
 * Explanation: Longest ZigZag path in blue nodes (right -> left -> right).
 *
 * Example 2:
 * Input: root = [1,1,1,null,1,null,null,1,1,null,1]
 * Output: 4
 * Explanation: Longest ZigZag path in blue nodes (left -> right -> left -> right).
 *
 * Example 3:
 * Input: root = [1]
 * Output: 0
 * Explanation: Tree has only one node.
 * 
 * Note:
 * Each tree has at most 50000 nodes..
 * Each node's value is between [1, 100].
 * 
 */
#include <utility>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int longestZigZag(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }

private:
    // 返回值为 pair，分别表示从当前节点向左和向右走的最长之字形路径的边数
    pair<int, int> dfs(TreeNode* node, int& ans) {
        if (!node) return {-1, -1}; // 空节点，没有边
        auto left = dfs(node->left, ans);
        auto right = dfs(node->right, ans);
        // 当前节点向左走：需要从右子节点过来（即左子节点的向右路径长度 + 1）
        int left_len = left.second + 1;
        // 当前节点向右走：需要从左子节点过来（即右子节点的向左路径长度 + 1）
        int right_len = right.first + 1;
        ans = max(ans, max(left_len, right_len));
        return {left_len, right_len};
    }
};
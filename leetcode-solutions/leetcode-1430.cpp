/*
 * 1430. Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree
 *
 * Given a binary tree where each path going from the root to any leaf form a valid sequence, check if a given string is a valid sequence in such binary tree. 
 * 
 * Example 1:
 * 
 * Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,0,1]
 * Output: true
 * Explanation: 
 * The path 0 -> 1 -> 0 -> 1 is a valid sequence (green color in the figure). 
 * Other valid sequences are: 
 * 0 -> 1 -> 1 -> 0 
 * 0 -> 0 -> 0
 * 
 * Example 2:
 * 
 * Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,0,1]
 * Output: false 
 * Explanation: The path 0 -> 0 -> 1 does not exist, therefore it is not even a sequence.
 * 
 * Example 3:
 * 
 * Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,1]
 * Output: false
 * Explanation: The path 0 -> 1 -> 1 is a sequence, but it is not a valid sequence.
 * 
 * Note:
 * 1 <= arr.length <= 5000
 * 0 <= arr[i] <= 9
 * Each node's value is between [0 - 9].
 * 
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        return dfs(root, arr, 0);
    }

private:
    bool dfs(TreeNode* node, vector<int>& arr, int index) {
        // 如果当前节点为空，或者当前节点的值与数组对应位置的值不相等，则此路径无效 [citation:2][citation:7]
        if (node == nullptr || node->val != arr[index]) {
            return false;
        }

        // 如果已经到达数组的最后一个元素，检查当前节点是否是叶子节点 [citation:5][citation:9]
        if (index == arr.size() - 1) {
            return node->left == nullptr && node->right == nullptr;
        }

        // 继续递归搜索左子树和右子树 [citation:2][citation:7]
        return dfs(node->left, arr, index + 1) || dfs(node->right, arr, index + 1);
    }
};

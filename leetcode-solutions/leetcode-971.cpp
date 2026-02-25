/**
 * 971. Flip Binary Tree To Match Preorder Traversal
 *
 * You are given the root of a binary tree with n nodes, where each node is uniquely assigned a value from 1 to n. You are also given a sequence of n values voyage, which is the desired pre-order traversal of the binary tree.
 *
 * Any node in the binary tree can be flipped by swapping its left and right subtrees. For example, flipping node 1 will have the following effect:
 *
 * Flip the smallest number of nodes so that the pre-order traversal of the tree matches voyage.
 *
 * Return a list of the values of all flipped nodes. You may return the answer in any order. If it is impossible to flip the nodes in the tree to make the pre-order traversal match voyage, return the list [-1].
 *
 * Example 1:
 *
 * Input: root = [1,2], voyage = [2,1]
 * Output: [-1]
 * Explanation: It is impossible to flip the nodes such that the pre-order traversal matches voyage.
 *
 * Example 2:
 *
 * Input: root = [1,2,3], voyage = [1,3,2]
 * Output: [1]
 * Explanation: Flipping node 1 swaps nodes 2 and 3, so the pre-order traversal matches voyage.
 *
 * Example 3:
 *
 * Input: root = [1,2,3], voyage = [1,2,3]
 * Output: []
 * Explanation: The tree's pre-order traversal already matches voyage, so no nodes need to be flipped.
 *
 * Constraints:
 *
 * The number of nodes in the tree is n.
 * n == voyage.length
 * 1 <= n <= 100
 * 1 <= Node.val, voyage[i] <= n
 * All the values in the tree are unique.
 * All the values in voyage are unique.
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

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
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        vector<int> result;
        int index = 0;
        
        if (dfs(root, voyage, index, result)) {
            return result;
        }
        return {-1};
    }
    
private:
    bool dfs(TreeNode* node, const vector<int>& voyage, int& index, vector<int>& result) {
        if (node == nullptr) {
            return true;
        }
        
        // If current node doesn't match the expected value in voyage
        if (node->val != voyage[index]) {
            return false;
        }
        
        index++;
        
        // Try to go left first (as per preorder traversal)
        if (node->left != nullptr && node->left->val != voyage[index]) {
            // Need to flip: swap left and right children
            result.push_back(node->val);
            swap(node->left, node->right);
        }
        
        // Continue DFS on left and right subtrees
        return dfs(node->left, voyage, index, result) && 
               dfs(node->right, voyage, index, result);
    }
};
/**
 * 1469. Find All The Lonely Nodes
 * 
 * In a binary tree, a lonely node is a node that is the only child of its parent node. The root of the tree is not lonely because it does not have a parent node.
 * 
 * Given the root of a binary tree, return an array containing the values of all lonely nodes in the tree. Return the list in any order.
 * 
 * Example 1:
 * 
 * Input: root = [1,2,3,null,4]
 * Output: [4]
 * Explanation: Light blue node is the only lonely node.
 * Node 1 is the root and is not lonely.
 * Nodes 2 and 3 have the same parent and are not lonely.
 * 
 * Example 2:
 * 
 * Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2]
 * Output: [6,2]
 * Explanation: Light blue nodes are lonely nodes.
 * Please remember that order doesn't matter, [2,6] is also an acceptable answer.
 * 
 * Note:
 * 1 <= root.val <= 10^5
 * The number of nodes in the tree is in the range [1, 10^4].
 * Each node's value is unique.
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
    vector<int> getLonelyNodes(TreeNode* root) {
        vector<int> result;
        dfs(root, result);
        return result;
    }

private:
    void dfs(TreeNode* node, vector<int>& res) {
        if (!node) return;

        // Check if left child exists and right child does not
        if (node->left && !node->right) {
            res.push_back(node->left->val);
        }
        // Check if right child exists and left child does not
        if (node->right && !node->left) {
            res.push_back(node->right->val);
        }

        // Recurse to children
        dfs(node->left, res);
        dfs(node->right, res);
    }
};

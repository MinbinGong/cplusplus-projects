/*
 * 1676. Lowest Common Ancestor of a Binary Tree IV
 * 
 * Given the root of a binary tree and an array of TreeNode objects nodes, return the lowest common ancestor (LCA) of all the nodes in nodes. All the nodes will exist in the tree, and all values of the tree's nodes are unique.
 * 
 * Example 1:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [4,7]
 * Output: 2
 * Explanation: The lowest common ancestor of nodes 4 and 7 is node 2.
 * 
 * Example 2:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [1]
 * Output: 1
 * Explanation: The lowest common ancestor of a single node is the node itself.
 * 
 * Example 3:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [7,6,2,4]
 * Output: 5
 * Explanation: The lowest common ancestor of the nodes 7, 6, 2, and 4 is node 5.
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 104].
 * -109 <= Node.val <= 109
 * All Node.val are unique.
 * All nodes[i] will exist in the tree.
 * All nodes[i] are distinct.
 * 
 */
#include <functional>
#include <unordered_set>
using namespace std;

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
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        // 用哈希集合存储所有目标节点的指针，便于 O(1) 查找
        unordered_set<TreeNode*> targets(nodes.begin(), nodes.end());
        
        // 定义深度优先搜索函数
        function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* node) -> TreeNode* {
            // 基本情况：空节点或当前节点是目标节点之一，直接返回
            if (!node || targets.count(node)) {
                return node;
            }
            
            // 递归搜索左右子树
            TreeNode* left = dfs(node->left);
            TreeNode* right = dfs(node->right);
            
            // 如果左右子树都返回非空，说明目标节点分布在两侧，当前节点即为 LCA
            if (left && right) {
                return node;
            }
            
            // 否则，返回非空的那一侧（可能为空，也可能为找到的 LCA 或目标节点）
            return left ? left : right;
        };
        
        return dfs(root);
    }
};
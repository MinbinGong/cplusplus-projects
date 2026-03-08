/**
 * 1660. Correct a Binary Tree
 * 
 * You have a binary tree with a small defect. There is exactly one invalid node where its right child incorrectly points to another node at the same depth but to the invalid node's right.
 * 
 * Given the root of the binary tree with this defect, root, return the root of the binary tree after removing this invalid node and every node underneath it (minus the node it incorrectly points to).
 * 
 * Custom testing:
 * The test input is read as 3 lines:
 * TreeNode root
 * int fromNode (not available to correctBinaryTree)
 * int toNode (not available to correctBinaryTree)
 * After the binary tree rooted at root is parsed, the TreeNode with value of fromNode will have its right child pointer pointing to the TreeNode with a value of toNode. Then, root is passed to correctBinaryTree.
 * 
 * Example 1:
 * Input: root = [1,2,3], fromNode = 2, toNode = 3
 * Output: [1,null,3]
 * Explanation: The node with value 2 is invalid, so remove it.
 * 
 * Example 2:
 * Input: root = [1,2,4,3,null,null,null], fromNode = 3, toNode = 1
 * Output: [1,2,4,null,null,null]
 * Explanation: The node with value 3 is invalid, so remove it.
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [3, 10^4].
 * -10^9 <= Node.val <= 10^9
 * All Node.val are unique.
 * fromNode != toNode
 * fromNode and toNode will exist in the tree and will be on the same depth.
 * toNode is to the right of fromNode.
 * fromNode.right is null in the initial tree from the input.
 * 
 */
#include <queue>
#include <unordered_set>
#include <functional>
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

class Solution1 {
public:
    TreeNode* correctBinaryTree(TreeNode* root) {
        // 队列存储当前节点及其父节点
        queue<pair<TreeNode*, TreeNode*>> q;
        q.push({root, nullptr});
        unordered_set<TreeNode*> vis; // 用于记录当前层的节点

        while (!q.empty()) {
            int levelSize = q.size();
            vis.clear(); // 每一层开始时清空，只记录当前层的节点

            // 先将当前层的所有节点加入 vis 集合
            vector<pair<TreeNode*, TreeNode*>> levelNodes;
            for (int i = 0; i < levelSize; ++i) {
                auto [node, parent] = q.front(); q.pop();
                levelNodes.push_back({node, parent});
                vis.insert(node);
            }

            // 检查并重建队列（加入下一层的节点）
            for (auto [node, parent] : levelNodes) {
                // 关键检测：如果当前节点的右孩子存在于 vis 集合中（即当前层），说明该右孩子是被错误指向的
                if (node->right && vis.count(node->right)) {
                    // 当前节点就是无效节点，通过父指针删除它
                    if (parent) {
                        if (parent->left == node) parent->left = nullptr;
                        else parent->right = nullptr;
                    }
                    return root; // 删除后直接返回
                }
                // 将下一层的节点加入队列
                if (node->left) q.push({node->left, node});
                if (node->right) q.push({node->right, node});
            }
        }
        return root;
    }
};

class Solution2 {
public:
    TreeNode* correctBinaryTree(TreeNode* root) {
        unordered_set<TreeNode*> vis;
        // 递归函数，返回处理后的子树根节点
        function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* node) -> TreeNode* {
            if (!node) return nullptr;
            // 如果右孩子已经被访问过，说明当前节点是无效的（其右指针指向了已访问节点）
            if (node->right && vis.count(node->right)) {
                return nullptr; // 移除当前节点及其子树
            }
            vis.insert(node);
            // 必须先右后左：因为错误指针指向右侧节点，需要先访问右侧确保其被标记
            node->right = dfs(node->right);
            node->left = dfs(node->left);
            return node;
        };
        return dfs(root);
    }
};
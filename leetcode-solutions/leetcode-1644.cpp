/*
 * 1644. Lowest Common Ancestor of a Binary Tree II
 *
 * Given the root of a binary tree, return the lowest common ancestor (LCA) of two given nodes, p and q. If either node p or q does not exist in the tree, return null. All values of the nodes in the tree are unique.
 * According to the definition of LCA on Wikipedia: "The lowest common ancestor of two nodes p and q in a binary tree T is the lowest node that has both p and q as descendants (where we allow a node to be a descendant of itself)". A descendant of a node x is a node y that is on the path from node x to some leaf node.
 * 
 * Example 1:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
 * Output: 3
 * Explanation: The LCA of nodes 5 and 1 is 3.
 * 
 * Example 2:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
 * Output: 5
 * Explanation: The LCA of nodes 5 and 4 is 5. A node can be a descendant of itself according to the definition of LCA.
 * 
 * Example 3:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 10
 * Output: null
 * Explanation: Node 10 does not exist in the tree, so return null.
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 104].
 * -109 <= Node.val <= 109
 * All Node.val are unique.
 * p != q
 * 
 */
#include <unordered_map>
#include <queue>
#include <unordered_set>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution1 {
private:
    bool foundP = false;
    bool foundQ = false;

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* lca = findLCA(root, p, q);
        // 只有当 p 和 q 都找到了，才返回 LCA，否则返回 nullptr
        if (foundP && foundQ) {
            return lca;
        }
        return nullptr;
    }

    // 这个函数执行标准的 LCA 查找，并顺便记录 p 和 q 是否出现
    TreeNode* findLCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return nullptr;

        // 后序遍历
        TreeNode* left = findLCA(root->left, p, q);
        TreeNode* right = findLCA(root->right, p, q);

        // 如果当前节点是 p 或 q，更新标记
        if (root == p) {
            foundP = true;
            return root; // 如果当前节点是目标，向上返回
        }
        if (root == q) {
            foundQ = true;
            return root;
        }

        // 核心 LCA 逻辑
        if (left && right) {
            return root; // p 和 q 分布在左右子树，当前节点是 LCA
        }
        // 否则，返回非空的子节点（如果存在）
        return left ? left : right;
    }
};

class Solution2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int mark = 0; // 最低位标记 p，次低位标记 q
        TreeNode* lca = dfs(root, p, q, mark);
        // 检查是否两个节点都找到了 (mark 的低两位都为 1，即 mark == 3)
        return (mark == 3) ? lca : nullptr;
    }

private:
    TreeNode* dfs(TreeNode* root, TreeNode* p, TreeNode* q, int& mark) {
        if (root == nullptr) return nullptr;

        TreeNode* left = dfs(root->left, p, q, mark);
        TreeNode* right = dfs(root->right, p, q, mark);

        // 找到 p，标记最低位
        if (root == p) {
            mark |= 1; // 二进制 01
            return root;
        }
        // 找到 q，标记次低位
        if (root == q) {
            mark |= 2; // 二进制 10
            return root;
        }

        // 如果左右子树各找到一个，当前节点是 LCA
        if (left && right) return root;
        return left ? left : right;
    }
};

class Solution3 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return nullptr;

        // 使用 map 记录每个节点的父节点
        unordered_map<TreeNode*, TreeNode*> parent;
        parent[root] = nullptr;
        queue<TreeNode*> que;
        que.push(root);

        // BFS 遍历树，记录父节点
        while (!que.empty()) {
            TreeNode* node = que.front();
            que.pop();
            if (node->left) {
                parent[node->left] = node;
                que.push(node->left);
            }
            if (node->right) {
                parent[node->right] = node;
                que.push(node->right);
            }
        }

        // 检查 p 和 q 是否存在于树中（即是否有父节点记录，根节点除外）
        // 注意：根节点虽然没有父节点，但它本身可能就是要找的节点
        bool pExists = (p == root) || parent.count(p);
        bool qExists = (q == root) || parent.count(q);

        if (!pExists || !qExists) {
            return nullptr;
        }

        // 收集 p 的所有祖先（包括 p 自身）
        unordered_set<TreeNode*> ancestors;
        while (p != nullptr) {
            ancestors.insert(p);
            p = parent[p];
        }

        // 从 q 开始向上找，第一个在祖先集合中的节点就是 LCA
        while (q != nullptr) {
            if (ancestors.count(q)) {
                return q;
            }
            q = parent[q];
        }

        return nullptr; // 理论上不会执行到这里
    }
};
/*
 * 1666. Change the Root of a Binary Tree
 *
 * Given the root of a binary tree and a leaf node, reroot the tree so that the leaf is the new root.
 * 
 * You can reroot the tree with k moves, where each move consists of swapping the parent of a node with its left or right child. Return the minimum number of moves required to move the given leaf node to the root of the tree.
 * 
 * Note that:
 * 
 * The input is only given as the root of a binary tree. You can design a class to store the parent of a node.
 * 
 * Example 1:
 * Input: root = [1,2,3,null,null,4,5,null,null,null,null,6], leaf = 6
 * Output: 3
 * Explanation: Move the leaf to root in 3 moves:
 * 1. Move node 2 to the root. Node 2 is the new root.
 * 2. Move node 4 to node 2.
 * 3. Move node 6 to node 4.
 * 
 * Example 2:
 * Input: root = [1,2,3,null,null,4,5,null,null,null,null,6], leaf = 5
 * Output: 4
 * Explanation: Move the leaf to root in 4 moves:
 * 1. Move node 2 to the root. Node 2 is the new root.
 * 2. Move node 4 to node 2.
 * 3. Move node 5 to node 4.
 * 4. Move node 6 to node 5.
 * 
 * Example 3:
 * Input: root = [1,2,3,null,null,4,5,null,null,null,null,6], leaf = 6
 * Output: 0
 * Explanation: The leaf is already at the root.
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [2, 1000].
 * -109 <= Node.val <= 109
 * All Node.val are unique.
 * leaf exists in the tree.
 * 
 */

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
    Node(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Solution {
public:
    Node* flipBinaryTree(Node* root, Node * leaf) {
        // 如果叶节点就是根节点，直接返回
        if (leaf == root) return root;
        
        // 保存当前节点的父节点，因为后面会修改
        Node* cur = leaf;
        Node* parent = cur->parent;
        
        // 将叶节点的左孩子指向其父节点，并断开父指针
        cur->left = parent;
        cur->parent = nullptr;
        
        // 从叶节点的父节点开始，沿着原路径向上处理
        Node* prev = cur;
        cur = parent;
        
        while (cur != root) {
            // 保存当前节点的原父节点
            Node* nextParent = cur->parent;
            
            // 处理当前节点的左右孩子
            // 如果当前节点的右孩子是上一个处理的节点
            if (cur->right == prev) {
                // 将右孩子改为左孩子
                cur->right = cur->left;
                cur->left = prev;
            } else {
                // 如果左孩子是上一个处理的节点
                cur->left = prev;
            }
            
            // 更新父指针
            cur->parent = prev;
            
            // 移动到下一个节点
            prev = cur;
            cur = nextParent;
        }
        
        // 处理根节点
        if (root->right == prev) {
            root->right = root->left;
            root->left = prev;
        } else {
            root->left = prev;
        }
        root->parent = prev;
        
        return leaf;
    }
};

/*
 * Convert Sorted List to Binary Search Tree
 * 
 * Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height-balanced binary search tree.
 * 
 * Example 1:
 * Input: head = [-10,-3,0,5,9]
 * Output: [0,-3,9,-10,null,5]
 * Explanation: One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.
 * 
 * Example 2:
 * Input: head = []
 * Output: []
 * 
 * Constraints:
 * The number of nodes in head is in the range [0, 2 * 104].
 * -105 <= Node.val <= 105
 * 
 */

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (!root) return nullptr;
        Node* first = nullptr;
        Node* last = nullptr;
        inorder(root, first, last);
        // 连接首尾形成循环链表
        first->left = last;
        last->right = first;
        return first;
    }

private:
    void inorder(Node* node, Node*& first, Node*& last) {
        if (!node) return;
        inorder(node->left, first, last);
        
        if (last) {
            // 将上一个节点（last）与当前节点连接
            last->right = node;
            node->left = last;
        } else {
            // 当前是最小节点，记录为头节点
            first = node;
        }
        last = node; // 更新最后一个节点为当前节点
        
        inorder(node->right, first, last);
    }
};
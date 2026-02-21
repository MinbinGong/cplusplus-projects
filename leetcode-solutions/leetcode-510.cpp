/*
 * Inorder Successor in BST II
 *
 * Given a node in a binary search tree, return the in-order successor of that node in the BST.
 * If that node has no in-order successor, return null.
 *
 * The successor of a node is the node with the smallest key greater than node.val.
 *
 * You will have direct access to the node but not to the root of the tree.
 * Each node will have a reference to its parent node.
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 104].
 * -105 <= Node.val <= 105
 * All Nodes will have unique values.
 * 
 */

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};

class Solution {
public:
    Node* inorderSuccessor(Node* node) {
        if (!node) return nullptr;

        // Case 1: node has a right child
        if (node->right) {
            node = node->right;
            while (node->left) {
                node = node->left;
            }
            return node;
        }

        // Case 2: no right child, move up via parent
        while (node->parent && node == node->parent->right) {
            node = node->parent;
        }
        // If we stopped because node is left child of its parent,
        // the parent is the successor. Otherwise, node->parent is null.
        return node->parent;
    }
};
/*
 * N-ary Tree Preorder Traversal
 *
 * Given the root of an n-ary tree, return the preorder traversal of its nodes' values.
 * 
 * Example:
 * Input: root = [1,null,3,2,4,null,5,6]
 * Output: [1,3,5,6,2,4]
 * 
 * Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
 * Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]
 * 
 * Note:
 * The number of nodes in the tree is in the range [0, 104].
 * 0 <= Node.val <= 104
 * The height of the n-ary tree is less than or equal to 1000.
 * 
 */
#include <vector>
#include <stack>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> result;
        if (!root) return result;
        
        stack<Node*> stk;
        stk.push(root);
        
        while (!stk.empty()) {
            Node* node = stk.top();
            stk.pop();
            result.push_back(node->val);
            
            // Push children in reverse order so that the leftmost child
            // is processed first (stack is LIFO)
            for (int i = node->children.size() - 1; i >= 0; --i) {
                if (node->children[i]) {
                    stk.push(node->children[i]);
                }
            }
        }
        
        return result;
    }
};
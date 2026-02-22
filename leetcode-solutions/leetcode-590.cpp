/*
 * N-ary Tree Postorder Traversal
 *
 * Given the root of an n-ary tree, return the postorder traversal of its nodes' values.
 * 
 * Example:
 * Input: root = [1,null,3,2,4,null,5,6]
 * Output: [5,6,3,2,4,1]
 * 
 * Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
 * Output: [2,6,14,11,7,3,12,8,4,13,9,10,5,1]
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
    vector<int> postorder(Node* root) {
        vector<int> result;
        if (!root) return result;
        
        stack<Node*> stk;      // for traversal
        stack<Node*> out;       // to reverse the order
        
        stk.push(root);
        
        while (!stk.empty()) {
            Node* node = stk.top();
            stk.pop();
            out.push(node);
            
            // Push children in order – they will be processed in reverse by out stack
            for (Node* child : node->children) {
                stk.push(child);
            }
        }
        
        // Pop from out to get postorder (children before root)
        while (!out.empty()) {
            result.push_back(out.top()->val);
            out.pop();
        }
        
        return result;
    }
};
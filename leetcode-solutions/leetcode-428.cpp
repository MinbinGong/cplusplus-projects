/*
 * Serialize and Deserialize N-ary Tree
 *
 * Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
 * Design an algorithm to serialize and deserialize an N-ary tree. An N-ary tree is a rooted tree in which each node has no more than N children. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that an N-ary tree can be serialized to a string and this string can be deserialized to the original tree structure.
 * 
 * Example 1:
 * Input: root = [1,null,3,2,4,null,5,6]
 * Output: [1,null,3,2,4,null,5,6]
 * 
 * Example 2:
 * Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
 * Output: [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [0, 10^4].
 * 0 <= Node.val <= 10^4
 * The height of the n-ary tree is less than or equal to 1000.
 * Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
 * 
 */
#include <vector>
#include <sstream>
#include <string>
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

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        if (!root) return "";
        ostringstream out;
        serializeHelper(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        if (data.empty()) return nullptr;
        istringstream in(data);
        return deserializeHelper(in);
    }

private:
    void serializeHelper(Node* node, ostringstream& out) {
        // Preorder: value then number of children, then recursively each child
        out << node->val << " " << node->children.size() << " ";
        for (Node* child : node->children) {
            serializeHelper(child, out);
        }
    }

    Node* deserializeHelper(istringstream& in) {
        int val, cnt;
        in >> val >> cnt;
        Node* node = new Node(val);
        for (int i = 0; i < cnt; ++i) {
            node->children.push_back(deserializeHelper(in));
        }
        return node;
    }
};
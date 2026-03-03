/**
 * 1516. Move Sub-Tree of N-Ary Tree
 * 
 * Given the root of an N-ary tree of unique values, and two nodes of the tree p and q.
 * You should move the subtree of the node p to become a direct child of node q.
 * If p is already a direct child of q, do not change anything.
 * Node p must be the last child in the children list of node q.
 * Node q may have no children.
 * Return the root of the tree after adjusting it.
 * 
 * Example 1:
 * Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14], p = 11, q = 8
 * Output: [1,null,2,3,4,5,null,null,6,7,null,11,null,8,null,9,10,null,null,12,null,13,null,null,14]
 * 
 * Example 2:
 * Input: root = [1,null,2,3,null,4,5,null,6,null,7,8,null,9,10,null,null,11,null,12,null,13,null,null,14], p = 13, q = 5
 * Output: [1,null,2,3,null,4,5,null,6,null,7,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
 * 
 * Note:
 * The number of nodes in the tree is between [2, 1000].
 * Each node has a unique value.
 * p != null
 * q != null
 * p and q are two different nodes (i.e. p != q).
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) { val = _val; }
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    Node* moveSubTree(Node* root, Node* p, Node* q) {
        if (!root || !p || !q) return root;
        if (p == q) return root;
        unordered_map<Node*, Node*> parent;
        parent[root] = nullptr;
        Node* pFound = nullptr;
        Node* qFound = nullptr;
        dfs(root, parent, p, q, pFound, qFound);
        if (!pFound || !qFound) return root;
        bool isAncestor = checkAncestor(pFound, qFound, parent);
        if (isAncestor) {
            Node* qParent = parent[qFound];
            removeChild(qParent, qFound);
            Node* pParent = parent[pFound];
            if (pParent) {
                removeChild(pParent, pFound);
                pParent->children.push_back(qFound);
                parent[qFound] = pParent;
            } else {
                parent[qFound] = nullptr;
                root = qFound;
            }
            qFound->children.push_back(pFound);
            parent[pFound] = qFound;
        } else {
            Node* pParent = parent[pFound];
            removeChild(pParent, pFound);
            qFound->children.push_back(pFound);
            parent[pFound] = qFound;
        }
        return root;
    }
private:
    void dfs(Node* node, unordered_map<Node*, Node*>& parent, Node* p, Node* q, Node*& pFound, Node*& qFound) {
        if (!node) return;
        if (node == p) pFound = node;
        if (node == q) qFound = node;
        for (Node* child : node->children) {
            parent[child] = node;
            dfs(child, parent, p, q, pFound, qFound);
        }
    }
    bool checkAncestor(Node* p, Node* q, unordered_map<Node*, Node*>& parent) {
        Node* curr = q;
        while (curr) {
            if (curr == p) return true;
            curr = parent[curr];
        }
        return false;
    }
    void removeChild(Node* parent, Node* child) {
        if (!parent) return;
        auto& children = parent->children;
        for (auto it = children.begin(); it != children.end(); ++it) {
            if (*it == child) {
                children.erase(it);
                break;
            }
        }
    }
};
/**
 * 1490. Clone N-ary Tree
 * 
 * Given a root of an N-ary tree, return a deep copy (clone) of the tree.
 * 
 * Each node in the n-ary tree contains a val (int) and a list (List[Node]) of its children.
 * 
 * class Node {
 *     public int val;
 *     public List<Node> children;
 * }
 * 
 * Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).
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
 * The depth of the n-ary tree is less than or equal to 1000.
 * The total number of nodes is between [0, 10^4].
 * 
 */
#include <vector>
#include <queue>
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

class Solution1 {
public:
    Node* cloneTree(Node* root) {
        if (!root) return nullptr;                 // 空节点直接返回
        
        // 先复制当前节点的值
        Node* newNode = new Node(root->val);
        
        // 递归复制所有子节点
        for (Node* child : root->children) {
            newNode->children.push_back(cloneTree(child));
        }
        
        return newNode;
    }
};

class Solution2 {
public:
    Node* cloneTree(Node* root) {
        if (!root) return nullptr;
        
        // 创建新根节点
        Node* newRoot = new Node(root->val);
        
        // 使用两个队列同步遍历：q 存放原树节点，qClone 存放对应的克隆节点
        queue<Node*> q;
        queue<Node*> qClone;
        q.push(root);
        qClone.push(newRoot);
        
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            Node* curClone = qClone.front(); qClone.pop();
            
            // 遍历当前节点的所有子节点
            for (Node* child : cur->children) {
                // 创建子节点的拷贝
                Node* childClone = new Node(child->val);
                curClone->children.push_back(childClone);
                
                // 将原节点和克隆节点入队，继续处理它们的子节点
                q.push(child);
                qClone.push(childClone);
            }
        }
        
        return newRoot;
    }
};
/*
 * Encode N-ary Tree to Binary Tree
 *
 * Design an algorithm to encode an N-ary tree into a binary tree and decode the binary tree to get the original N-ary
 * tree. An N-ary tree is a rooted tree in which each node has no more than N children. Similarly, a binary tree is a
 * rooted tree in which each node has no more than 2 children. There is no restriction on how your encode/decode
 * algorithm should work. You just need to ensure that an N-ary tree can be encoded to a binary tree and this binary
 * tree can be decoded to the original N-nary tree structure.
 *
 * Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by
 * the null value (See examples).
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
 * Do not use class member/global/static variables to store states. Your encode and decode algorithms should be
 * stateless.
 *
 */
// Definition for a Node.
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

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
 public:
  // Encodes an n-ary tree to a binary tree.
  TreeNode* encode(Node* root) {
    if (!root) return nullptr;

    // 创建二叉树根节点
    TreeNode* newRoot = new TreeNode(root->val);

    // 如果有子节点，将第一个子节点编码后挂在左孩子位置
    if (!root->children.empty()) {
      newRoot->left = encode(root->children[0]);

      // 其余子节点作为右链依次连接
      TreeNode* curr = newRoot->left;
      for (int i = 1; i < root->children.size(); ++i) {
        curr->right = encode(root->children[i]);
        curr = curr->right;
      }
    }

    return newRoot;
  }

  // Decodes your binary tree to an n-ary tree.
  Node* decode(TreeNode* root) {
    if (!root) return nullptr;

    // 创建N叉树根节点
    Node* newRoot = new Node(root->val);

    // 从左孩子开始，沿着右链收集所有子节点
    TreeNode* curr = root->left;
    while (curr) {
      newRoot->children.push_back(decode(curr));
      curr = curr->right;
    }

    return newRoot;
  }
};
/*
 * Complete Binary Tree Inserter
 *
 * A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, and all
 * nodes are as far left as possible.
 *
 * Design an algorithm to insert a new node to a complete binary tree keeping it complete after the insertion.
 *
 * Implement the CBTInserter class:
 *
 * CBTInserter(TreeNode root) Initializes the data structure with the root of the complete binary tree.
 * int insert(int v) Inserts a TreeNode into the tree with value Node.val == val so that the tree remains complete, and
 * returns the value of the parent of the inserted TreeNode. TreeNode get_root() Returns the root node of the tree.
 *
 * Example 1:
 * Input
 * ["CBTInserter", "insert", "insert", "get_root"]
 * [[[1, 2]], [3], [4], []]
 * Output
 * [null, 1, 2, [1, 2, 3, 4]]
 *
 * Explanation
 * CBTInserter cBTInserter = new CBTInserter([1, 2]);
 * cBTInserter.insert(3);  // return 1
 * cBTInserter.insert(4);  // return 2
 * cBTInserter.get_root(); // return [1, 2, 3, 4]
 *
 * Note:
 * The initial given tree is complete and contains between 1 and 1000 nodes.
 * CBTInserter.insert is called at most 10000 times per test case.
 * Every value of a given or inserted node is between 0 and 5000.
 *
 */
#include <queue>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class CBTInserter {
 private:
  TreeNode* root;
  queue<TreeNode*> q;  // nodes that are not yet full (missing at least one child)

 public:
  CBTInserter(TreeNode* root) {
    this->root = root;
    // BFS to collect all nodes that have at least one missing child
    queue<TreeNode*> bfs;
    bfs.push(root);
    while (!bfs.empty()) {
      TreeNode* node = bfs.front();
      bfs.pop();
      if (node->left == nullptr || node->right == nullptr) {
        q.push(node);
      }
      if (node->left) bfs.push(node->left);
      if (node->right) bfs.push(node->right);
    }
  }

  int insert(int v) {
    TreeNode* newNode = new TreeNode(v);
    TreeNode* parent = q.front();  // the first incomplete node
    if (parent->left == nullptr) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
      q.pop();  // now parent is full, remove it
    }
    q.push(newNode);  // new node is incomplete (no children yet)
    return parent->val;
  }

  TreeNode* get_root() { return root; }
};
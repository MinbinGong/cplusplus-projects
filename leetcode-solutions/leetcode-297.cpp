/*
 * Serialize and Deserialize Binary Tree
 *
 * Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.
 *
 * Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
 * 
 */
#include <queue>
#include <string>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
  const char DELIM = '#';
  const char NULL_FLAG = '!';

  void processNext(const std::string& data, int& i, queue<TreeNode*>& _queue, TreeNode*& p) {
    int initial = i;
    i = data.find(DELIM, i);
    ++i;

    string temp = data.substr(initial, i - initial - 1);
    if (temp[0] != NULL_FLAG) {
      p = new TreeNode(stoi(temp));
      _queue.push(p);
    }
  }

 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    std::string result = "";
    std::queue<TreeNode*> _queue;
    if (!root)
      return result;
    else {
      _queue.push(root);
      while (!_queue.empty()) {
        TreeNode* current = _queue.front();
        _queue.pop();
        if (current) {
          result += std::to_string(current->val);
          _queue.push(current->left);
          _queue.push(current->right);
        } else
          result += NULL_FLAG;
        result += DELIM;
      }
    }
    return result;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    int index = 0;
    TreeNode* root = nullptr;
    if (data.empty())
      return root;
    else {
      std::queue<TreeNode*> _queue;
      processNext(data, index, _queue, root);
      while (!_queue.empty()) {
        TreeNode* current = _queue.front();
        _queue.pop();
        processNext(data, index, _queue, current->left);
        processNext(data, index, _queue, current->right);
      }
      return root;
    }
  }
};
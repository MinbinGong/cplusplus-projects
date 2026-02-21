/*
 * Serialize and Deserialize Binary Tree
 *
 * Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.
 *
 * Constraints:
 * The number of nodes in the tree is in the range [0, 104].
 * -1000 <= Node.val <= 1000
 */
#include <string>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
  // Decodes your encoded data to tree.
  TreeNode *deserializeCore(string const &data, int &curr, int end) {
    if (curr > end) {
      return nullptr;
    }

    // parse until we find a ','
    int it = curr;
    while (data[it] != ',') {
      ++it;
    }

    // what did we just parsed?
    string parsed = data.substr(curr, it - curr);

    // SUBTLE
    // skip past the ','
    curr = ++it;

    if (parsed == "$") {
      return nullptr;
    }

    TreeNode *pRoot = new TreeNode(stoi(parsed));
    pRoot->left = deserializeCore(data, curr, end);
    pRoot->right = deserializeCore(data, curr, end);

    return pRoot;
  }

 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode *root) {
    if (!root) {
      return "$,";
    }

    ostringstream oss{};
    oss << root->val << "," << serialize(root->left) << serialize(root->right);

    return oss.str();
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(string data) {
    TreeNode *pRoot{nullptr};

    int curr{0};
    int end{static_cast<int>(data.size()) - 1};

    return deserializeCore(data, curr, end);
  }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
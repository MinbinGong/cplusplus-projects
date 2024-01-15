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
#include <list>
#include <sstream>
#include <string>

struct TreeNode {
    int val = 0;
    TreeNode *left = nullptr, *right = nullptr;
    TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

std::string serializeDFS(TreeNode *root, std::string str) {
    if (root == nullptr) {
        str += "null,";
    } else {
        str += std::to_string(root->val) + ",";
        str += serializeDFS(root->left, str);
        str += serializeDFS(root->right, str);
    }

    return str;
}

std::string serialize(TreeNode *root) { return serializeDFS(root, ""); }

TreeNode *deserializeDFS(std::list<std::string> &l) {
    if (l.front() == "null") {
        l.pop_front();
        return nullptr;
    }

    TreeNode *root = new TreeNode(std::stoi(l.front()));
    l.pop_front();
    root->left = deserializeDFS(l);
    root->right = deserializeDFS(l);

    return root;
}

TreeNode *deserialize(std::string data) {
    std::stringstream ss(data);
    std::list<std::string> l;

    std::string tmp;
    while (getline(ss, tmp, ',')) {
        l.push_back(tmp);
    }

    return deserializeDFS(l);
}

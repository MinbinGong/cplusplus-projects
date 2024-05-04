/*
 * Populating Next Right Pointers in Each Node
 *
 * You are given a perfect binary tree where all leaves are on the same level,
 * and every parent has two children.
 * The binary tree has the following definition:
 * struct Node {
 *   int val;
 *   Node *left;
 *   Node *right;
 *   Node *next;
 * }
 *
 * Populate each next pointer to point to its next right node.
 * If there is no next right node, the next pointer should be set to NULL.
 * Initially, all next pointers are set to NULL.
 */

struct Node {
    int val = 0;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *next = nullptr;

    explicit Node(int x = 0, Node *l = nullptr, Node *r = nullptr, Node *n = nullptr) : val(x), left(l), right(r), next(n) {}
};

Node *connect(Node *root) {
    if (root == nullptr) {
        return nullptr;
    }

    vector<vector<Node *>> lvl;
    queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        vector<Node *> temp;

        for (int i = 0; i < size; ++i) {
            Node *node = q.front();
            q.pop();

            if (node->left) {
                q.push(node->left);
            }

            if (node->right) {
                q.push(node->right);
            }

            temp.push(node);
        }

        temp.push_back(nullptr);
        lvl.push_back(temp);
    }

    for (int i = 0; i < lvl.size(); ++i) {
        for (int j = 0; j < lvl[i].size() - 1; ++j) {
            lvl[i][j]->next = lvl[i][j + 1];
        }
    }

    return root;
}

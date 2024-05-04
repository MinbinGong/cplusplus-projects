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
    Node *r = root;
    while (root && root->left) {
        Node *next = root->left;
        while (root) {
            root->left->next = root->right;
            root->right->next = root->next ? root->next->left : nullptr;
            root = root->next;
        }
        root = next;
    }

    return r;
}

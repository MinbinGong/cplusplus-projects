/*
 * Construct Binary Tree from Inorder and Postorder Traversal
 * Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree
 * and postorder is the postorder traversal of the same tree, construct and return the binary tree.
 *
 * Constraints:
 * 1. 1 <= inorder.length <= 3000
 * 2. postorder.length == inorder.length
 * 3. -3000 <= inorder[i], postorder[i] <= 3000
 * 4. inorder and postorder consist of unique values.
 * 5. Each value of postorder also appears in inorder.
 * 6. inorder is guaranteed to be the inorder traversal of the tree.
 * 7. postorder is guaranteed to be the postorder traversal of the tree.
 */
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    explicit TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

int findPosition(vector<int> &inorder, int element) {
    for (int i = 0; i < inorder.size(); i++) {
        if (inorder[i] == element) {
            return i;
        }
    }
    return -1;
}

TreeNode* buildTreeUtil(vector<int> &postorder, vector<int> &inorder, int &index, int start, int end) {
    if (index <0 or start > end) {
        return nullptr;
    }

    int element = postorder[index--];
    TreeNode *root = new TreeNode(element);
    int position = findPosition(inorder, element);

    root->right = buildTreeUtil(postorder, inorder, index, position + 1, end);
    root->left = buildTreeUtil(postorder, inorder, index, start, position - 1);

    return root;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    int n = postorder.size();
    int postOrderIndex = n - 1;
    return buildTreeUtil(postorder, inorder, postOrderIndex, 0, n - 1);
}


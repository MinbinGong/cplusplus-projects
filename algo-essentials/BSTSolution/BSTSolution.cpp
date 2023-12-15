// BSTSolution.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

struct TreeNode {
    int val = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode(int x = 0, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

std::vector<int> preorderTraversal(TreeNode* root) {
    std::vector<int> result;
    TreeNode *cur = root, *prev = nullptr;

    while (cur != nullptr) {
        if (cur->left == nullptr) {
            result.push_back(cur->val);
            prev = cur;
            cur = cur->right;
        } else {
            TreeNode* node = cur->left;
            while (node->right != nullptr && node->right != cur) {
                node = node->right;
            }

            if (node->right == nullptr) {
                result.push_back(cur->val);
                node->right = cur;
                prev = cur;
                cur = cur->left;
            } else {
                node->right = nullptr;
                cur = cur->right;
            }
        }
    }

    return result;
}

std::vector<int> inorderTraversal(TreeNode* root) {
    std::vector<int> result;
    TreeNode *cur = root, *prev = nullptr;

    while (cur != nullptr) {
        if (cur->left == nullptr) {
            result.push_back(cur->val);
            prev = cur;
            cur = cur->right;
        } else {
            TreeNode* node = cur->left;
            while (node->right != nullptr && node->right != cur) {
                node = node->right;
            }

            if (node->right == nullptr) {
                node->right = cur;
                cur = cur->left;
            } else {
                result.push_back(cur->val);
                node->right = nullptr;
                prev = cur;
                cur = cur->right;
            }
        }
    }

    return result;
}
int main() { std::cout << "Hello World!\n"; }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files
//   to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

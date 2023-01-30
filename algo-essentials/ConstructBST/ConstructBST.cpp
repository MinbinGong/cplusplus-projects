// ConstructBST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

struct TreeNode
{
    int val = 0;
    TreeNode* left = nullptr, * right = nullptr;
    TreeNode(int x = 0, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

template <typename InputIterator>
TreeNode* buildTree(InputIterator pre_first, InputIterator pre_last, InputIterator in_first, InputIterator in_last)
{
    if (pre_first == pre_last)
    {
        return nullptr;
    }

    if (in_first == in_last)
    {
        return nullptr;
    }

    auto root = new TreeNode(*pre_first);
    auto inRootPos = std::find(in_first, in_last, *pre_first);
    auto leftSize = std::distance(in_first, inRootPos);

    root->left = buildTree(std::next(pre_first), std::next(pre_first, leftSize + 1), in_first, std::next(in_first, leftSize));
    root->right = buildTree(std::next(pre_first, leftSize + 1), pre_last, std::next(inRootPos), in_last);

    return root;
}

TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
{
    return buildTree(std::begin(preorder), std::end(preorder), std::begin(inorder), std::end(inorder));
}

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

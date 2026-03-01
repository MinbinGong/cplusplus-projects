/*
 * 1305. All Elements in Two Binary Search Trees
 * 
 * Given two binary search trees root1 and root2.
 * 
 * Return a list containing all the integers from both trees sorted in ascending order.
 * 
 * Example 1:
 * Input: root1 = [2,1,4], root2 = [1,0,3]
 * Output: [0,1,1,2,3,4]
 * 
 * Example 2:
 * Input: root1 = [0,-10,10], root2 = [5,1,7,0,2]
 * Output: [-10,0,0,1,2,5,7,10]
 * 
 * Example 3:
 * Input: root1 = [], root2 = [5,1,7,0,2]
 * Output: [0,1,2,5,7]
 * 
 * Example 4:
 * Input: root1 = [0,-10,10], root2 = []
 * Output: [-10,0,10]
 * 
 * Note:
 * Each tree has at most 5000 nodes.
 * Each node's value is between [-10^5, 10^5].
 * 
 */
#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> list1, list2;
        // 中序遍历得到有序数组
        inorder(root1, list1);
        inorder(root2, list2);
        
        // 合并两个有序数组
        vector<int> result;
        int i = 0, j = 0;
        while (i < list1.size() && j < list2.size()) {
            if (list1[i] < list2[j]) {
                result.push_back(list1[i++]);
            } else {
                result.push_back(list2[j++]);
            }
        }
        // 将剩余元素加入结果
        while (i < list1.size()) result.push_back(list1[i++]);
        while (j < list2.size()) result.push_back(list2[j++]);
        
        return result;
    }

private:
    void inorder(TreeNode* root, vector<int>& list) {
        if (!root) return;
        inorder(root->left, list);
        list.push_back(root->val);
        inorder(root->right, list);
    }
};
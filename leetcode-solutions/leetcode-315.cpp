/*
 * Count of Smaller Numbers After Self
 * 
 * Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].
 * 
 * Example 1:
 * Input: nums = [5,2,6,1]
 * Output: [2,1,1,0]
 * Explanation:
 * To the right of 5 there are 2 smaller elements (2 and 1).
 * To the right of 2 there is only 1 smaller element (1).
 * To the right of 6 there is 1 smaller element (1).
 * To the right of 1 there is 0 smaller element.
 * 
 * Example 2:
 * Input: nums = [-1]
 * Output: [0]
 * 
 * Example 3:
 * Input: nums = [-1,-1]
 * Output: [0,0]
 * 
 */
#include <vector>
using namespace std;

class Solution {
  struct Node {
    int val;
    int smaller;  // smaller is the number of nodes on its left side
    Node *left, *right;
    Node(int v, int s) : val(v), smaller(s) {
      left = nullptr;
      right = nullptr;
    };
  };

  void insertNode(Node *&node, int v, int &ret) {
    if (!node) {
      node = new Node(v, 0);
    } else {
      if (v > node->val) {
        ret += node->smaller + 1;  // the number of nodes on its left side and the node itself
        insertNode(node->right, v, ret);
      } else if (v == node->val) {
        ret += node->smaller;  // the number of node on its left side only
        insertNode(node->right, v, ret);
      } else {
        node->smaller++;  // no adding. But since we add one node to its left side, increase the count of smeller
        insertNode(node->left, v, ret);
      }
    }
  }

 public:
  vector<int> countSmaller(vector<int> &nums) {
    vector<int> ret(nums.size());
    Node *root = nullptr;
    for (int i = nums.size() - 1; i >= 0; --i) {
      insertNode(root, nums[i], ret[i]);
    }
    return ret;
  }
};
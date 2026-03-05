/*
 * 1586. Binary Search Tree Iterator
 *
 * Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):
 * 
 * BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
 * boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
 * int next() Moves the pointer to the right, then returns the number at the pointer.
 * Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.
 * 
 * You may assume that next() calls will always be valid. That is, there will be at least a next number in the in-order traversal when next() is called.
 * 
 * Example 1:
 * Input
 * ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
 * [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
 * Output
 * [null, 3, 7, true, 9, true, 15, true, 20, false]
 * 
 * Explanation
 * BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
 * bSTIterator.next();    // return 3
 * bSTIterator.next();    // return 7
 * bSTIterator.hasNext(); // return True
 * bSTIterator.next();    // return 9
 * bSTIterator.hasNext(); // return True
 * bSTIterator.next();    // return 15
 * bSTIterator.hasNext(); // return True
 * bSTIterator.next();    // return 20
 * bSTIterator.hasNext(); // return False
 * 
 * Example 2:
 * Input
 * ["BSTIterator", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
 * [[[1, null, 2]], [], [], [], [], [], []]
 * Output
 * [null, 1, true, 2, false, null, false]
 * 
 * Explanation
 * BSTIterator bSTIterator = new BSTIterator([1, null, 2]);
 * bSTIterator.next();    // return 1
 * bSTIterator.hasNext(); // return True
 * bSTIterator.next();    // return 2
 * bSTIterator.hasNext(); // return False
 * 
 * Constraints:
 * The number of nodes in the tree is in the range [1, 10^5].
 * 0 <= Node.val <= 10^6
 * At most 10^5 calls will be made to hasNext, and next.
 * 
 */
#include <stack>
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

class BSTIterator {
private:
    stack<TreeNode*> nodeStack;      // 用于中序遍历的栈
    vector<TreeNode*> visitedList;   // 按顺序存储已访问的节点
    int currentIdx;                  // 当前指针在 visitedList 中的索引

public:
    BSTIterator(TreeNode* root) {
        currentIdx = -1;  // 初始化为 -1，表示指向第一个元素之前
        // 初始化栈：将根节点到最左边节点的路径压栈
        while (root) {
            nodeStack.push(root);
            root = root->left;
        }
    }
    
    bool hasNext() {
        // 如果当前索引之后还有已访问的节点，或者栈中还有未遍历的节点
        return currentIdx + 1 < visitedList.size() || !nodeStack.empty();
    }
    
    int next() {
        // 如果当前索引之后还有已访问的节点，直接使用
        if (currentIdx + 1 < visitedList.size()) {
            currentIdx++;
            return visitedList[currentIdx]->val;
        }
        
        // 否则从栈中取出下一个节点
        TreeNode* node = nodeStack.top();
        nodeStack.pop();
        
        // 将当前节点加入已访问列表
        visitedList.push_back(node);
        currentIdx = visitedList.size() - 1;
        
        // 处理右子树：将右子树的最左边路径压栈
        TreeNode* temp = node->right;
        while (temp) {
            nodeStack.push(temp);
            temp = temp->left;
        }
        
        return node->val;
    }
    
    bool hasPrev() {
        // 当前索引大于 0 时才有前驱
        return currentIdx > 0;
    }
    
    int prev() {
        // 指针左移并返回对应值
        currentIdx--;
        return visitedList[currentIdx]->val;
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * bool param_1 = obj->hasNext();
 * int param_2 = obj->next();
 * bool param_3 = obj->hasPrev();
 * int param_4 = obj->prev();
 */
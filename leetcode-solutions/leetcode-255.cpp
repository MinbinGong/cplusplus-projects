/*
 * Verify Preorder Sequence in Binary Search Tree
 *
 * Given an array of unique integers preorder, return true if it is the correct preorder traversal sequence of a binary
 * search tree.
 *
 * Constraints:
 * 1. 1 <= preorder.length <= 104
 * 2. 1 <= preorder[i] <= 104
 * 3. All the elements of preorder are unique.
 */
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

class Solution1 {
 public:
  bool verifyPreorder(vector<int>& preorder) {
    stack<int> stk;
    // 初始化最小值为整数的最小值，因为第一个节点没有下限约束
    int min = INT_MIN;

    for (int val : preorder) {
      // 右子树的节点值不能小于其根节点的值，这个根节点值已被记录在min中
      if (val < min) {
        return false;
      }

      // 当当前值大于栈顶元素时，说明栈顶元素所在的左子树已遍历完，
      // 我们需要找到这个当前节点属于哪个根节点的右子树。
      // 不断弹出小于当前值的栈顶，最后一个被弹出的就是当前节点的根节点，
      // 将其记录为新的下限 min。
      while (!stk.empty() && val > stk.top()) {
        min = stk.top();
        stk.pop();
      }

      // 当前节点入栈，等待处理其右子树
      stk.push(val);
    }
    return true;
  }
};

class Solution2 {
 public:
  bool verifyPreorder(vector<int>& preorder) {
    // 将数组本身当作栈使用，用 i 来指向栈顶
    int i = 0;
    int min = INT_MIN;

    for (int val : preorder) {
      if (val < min) {
        return false;
      }

      // 当当前值大于"栈顶"（即数组中 i-1 位置的元素）时，执行出栈操作
      // 出栈就是移动 i 指针，并将出栈的值更新为新的下限
      while (i > 0 && val > preorder[i - 1]) {
        min = preorder[i - 1];
        i--;
      }

      // 将当前值压入栈顶
      preorder[i] = val;
      i++;
    }
    return true;
  }
};

class Solution3 {
 public:
  bool verifyPreorder(vector<int>& preorder) { return verify(preorder, 0, preorder.size() - 1, INT_MIN, INT_MAX); }

 private:
  bool verify(vector<int>& preorder, int start, int end, int min, int max) {
    if (start > end) return true;

    int rootVal = preorder[start];
    // 检查当前节点是否在允许的范围内
    if (rootVal <= min || rootVal >= max) return false;

    // 找到第一个大于根节点的位置，划分左右子树
    int splitIndex = start + 1;
    while (splitIndex <= end && preorder[splitIndex] < rootVal) {
      splitIndex++;
    }

    // 递归检查左子树 [start+1, splitIndex-1] 和右子树 [splitIndex, end]
    return verify(preorder, start + 1, splitIndex - 1, min, rootVal) && verify(preorder, splitIndex, end, rootVal, max);
  }
};
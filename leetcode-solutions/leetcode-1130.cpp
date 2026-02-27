/**
 * 1130. Minimum Cost Tree From Leaf Values
 *
 * Given an array arr of positive integers, consider all binary trees such that:
 *
 * Each node has either 0 or 2 children;
 * The values of arr correspond to the values of each leaf in an in-order traversal of the tree.
 * The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree, respectively.
 * Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node. It is guaranteed this sum fits into a 32-bit integer.
 *
 * A node is a leaf if and only if it has zero children.
 *
 * Example 1:
 * Input: arr = [6,2,4]
 * Output: 32
 * Explanation: There are two possible trees shown.
 * The first has a non-leaf node sum 36, and the second has non-leaf node sum 32.
 *
 * Example 2:
 * Input: arr = [4,11]
 * Output: 44
 * Explanation: The tree is [4, 11].
 * 
 * Note:
 * The number of nodes in the tree is in the range [2, 40].
 * 1 <= arr[i] <= 15
 * 
 */
#include <vector>
#include <stack>
#include <climits>

class Solution {
public:
    int mctFromLeafValues(std::vector<int>& arr) {
        int totalCost = 0;
        std::stack<int> st;
        st.push(INT_MAX); // sentinel to avoid empty stack checks

        for (int num : arr) {
            // While the current value is >= the top of the stack,
            // pop and combine with the smaller neighbor
            while (st.top() <= num) {
                int mid = st.top();
                st.pop();
                totalCost += mid * std::min(st.top(), num);
            }
            st.push(num);
        }

        // After processing all numbers, combine remaining elements
        while (st.size() > 2) {
            int top = st.top();
            st.pop();
            totalCost += top * st.top();
        }

        return totalCost;
    }
};
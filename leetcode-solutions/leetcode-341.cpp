/*
 * Flatten Nested List Iterator
 *
 * Given a nested list of integers, implement an iterator to flatten it.
 *
 * Each element is either an integer, or a list -- whose elements may also be integers or other lists.
 *
 * Example 1:
 * Input: [[1,1],2,[1,1]]
 * Output: [1,1,2,1,1]
 * Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should
 * be: [1,1,2,1,1].
 *
 * Example 2:
 * Input: [1,[4,[6]]]
 * Output: [1,4,6]
 * Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should
 * be: [1,4,6].
 *
 */
#include <vector>
#include <stack>
using namespace std;

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 */
class NestedInteger {
 public:
  // Return true if this NestedInteger holds a single integer, rather than a nested list.
  bool isInteger() const;

  // Return the single integer that this NestedInteger holds, if it holds a single integer
  // The result is undefined if this NestedInteger holds a nested list
  int getInteger() const;

  // Return the nested list that this NestedInteger holds, if it holds a nested list
  // The result is undefined if this NestedInteger holds a single integer
  const vector<NestedInteger> &getList() const;
};

class NestedIterator {
 private:
  stack<NestedInteger> st;

 public:
  NestedIterator(vector<NestedInteger> &nestedList) {
    // Push all elements in reverse order so that the first element is on top
    for (int i = nestedList.size() - 1; i >= 0; --i) {
      st.push(nestedList[i]);
    }
  }

  int next() {
    // hasNext() must have been called to ensure the top is an integer
    int val = st.top().getInteger();
    st.pop();
    return val;
  }

  bool hasNext() {
    while (!st.empty()) {
      NestedInteger curr = st.top();
      if (curr.isInteger()) {
        return true;  // Found an integer, ready to be returned
      }
      // Otherwise it's a list: pop it and push its elements in reverse order
      st.pop();
      const vector<NestedInteger> &list = curr.getList();
      for (int i = list.size() - 1; i >= 0; --i) {
        st.push(list[i]);
      }
    }
    return false;  // Stack empty, no more integers
  }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
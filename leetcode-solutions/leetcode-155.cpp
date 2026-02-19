/*
 * Min Stack
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 * 
 * Implement the min_stack class:
 * 
 * min_stack() Initializes the stack object.
 * void push(int val) Pushes the element val onto the stack.
 * void pop() Removes the element on the top of the stack.
 * int top() Gets the top element of the stack.
 * int get_min() Retrieves the minimum element in the stack.
 * You must implement a solution with O(1) time complexity for each function.
 */
#include <stack>
using namespace std;

class min_stack {
 private:
  stack<int> s, min_s;

 public:
  min_stack() = default;
  ~min_stack() = default;

  void push(int x) {
    s.push(x);
    if (min_s.empty() || min_s.top() >= x) {
      min_s.push(x);
    }
  }

  void pop() {
    if (!min_s.empty() && min_s.top() == s.top()) {
      min_s.pop();
    }
    s.pop();
  }

  int top() { return s.top(); }

  int get_min() { return min_s.top(); }
};
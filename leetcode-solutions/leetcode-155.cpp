/*
  Min Stack

  题目描述
  设计一个最小栈，除了需要支持常规栈的操作外，还需要支持在 O(1) 时间内查询栈内最小
  值的功能。

  题解
  我们可以额外建立一个新栈，栈顶表示原栈里所有值的最小值。每当在原栈里插入一个数字
  时，若该数字小于等于新栈栈顶，则表示这个数字在原栈里是最小值，我们将其同时插入新栈内。
  每当从原栈里取出一个数字时，若该数字等于新栈栈顶，则表示这个数是原栈里的最小值之一，
  我们同时取出新栈栈顶的值。
  一个写起来更简单但是时间复杂度略高的方法是，我们每次插入原栈时，都向新栈插入一次
  原栈里所有值的最小值（新栈栈顶和待插入值中小的那一个）；每次从原栈里取出数字时，同样
  取出新栈的栈顶。这样可以避免判断，但是每次都要插入和取出。我们这里只展示第一种写法。
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
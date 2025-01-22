/*
  Implement Queue using Stacks

  题目描述
  尝试使用栈（stack）来实现队列（queue）。

  题解
  我们可以用两个栈来实现一个队列：因为我们需要得到先入先出的结果，所以必定要通过一
  个额外栈翻转一次数组。这个翻转过程既可以在插入时完成，也可以在取值时完成。
 */
#include <stack>
using namespace std;

class my_queue {
  stack<int> in, out;

  void in_to_out() {
    if (out.empty()) {
      while (!in.empty()) {
        int x = in.top();
        in.pop();
        out.push(x);
      }
    }
  }

 public:
  my_queue() = default;

  void push(int x) { in.push(x); }

  int pop() {
    in_to_out();
    int x = out.top();
    out.pop();
    return x;
  }

  int peek() {
    in_to_out();
    return out.top();
  }

  bool empty() { return in.empty() && out.empty(); }
};
#include <stack>
#include <string>

bool isValid(std::string const& s) {
  std::string left = "([{";
  std::string right = ")]}";
  std::stack<char> stk;

  for (auto c : s) {
    if (left.find(c) != std::string::npos) {
      stk.push(c);
    } else {
      if (stk.empty() || stk.top() != left[right.find(c)]) {
        return false;
      } else {
        stk.pop();
      }
    }
  }

  return stk.empty();
}
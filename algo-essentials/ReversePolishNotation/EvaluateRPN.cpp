#include <climits>
#include <stdexcept>
#include <string>
#include <vector>

int evaluateRPN(std::vector<std::string>& tokens) {
  const std::string& token = tokens.back();
  tokens.pop_back();

  int ret{INT_MIN};
  if (std::string("+-*/").find(token) == std::string::npos) {
    ret = std::stoi(token);
  } else {
    int y = evaluateRPN(tokens);
    int x = evaluateRPN(tokens);

    switch (token[0]) {
      case '+':
        ret = x + y;
        break;
      case '-':
        ret = x - y;
        break;
      case '*':
        ret = x * y;
        break;
      case '/':
        ret = x / y;
        break;
      default:
        throw std::runtime_error("Not supported");
        break;
    }
  }

  return ret;
}
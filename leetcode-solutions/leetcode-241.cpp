/*
Different ways to add parentheses

题目描述
给定一个只包含加、减和乘法的数学表达式，求通过加括号可以得到多少种不同的结果。

题解
利用分治思想，我们可以把加括号转化为，对于每个运算符号，先执行处理两侧的数学表达
式，再处理此运算符号。注意边界情况，即字符串内无运算符号，只有数字
 */
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<int> diffWaysToCompute(string &input) {
  vector<int> data;
  vector<char> ops;

  int num = 0;
  char op = ' ';
  istringstream ss(input + "+");
  while (ss >> num && ss >> op) {
    data.push_back(num);
    ops.push_back(op);
  }

  int n = data.size();
  vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>()));
  for (int i = 0; i < n; ++i) {
    for (int j = i; j >= 0; --j) {
      if (i == j) {
        dp[j][i].push_back(data[i]);
        continue;
      }

      for (int k = j; k < i; ++k) {
        for (auto left : dp[j][k]) {
          for (auto right : dp[k + 1][i]) {
            int val = 0;
            switch (ops[k]) {
              case '+':
                val = left + right;
                break;
              case '-':
                val = left - right;
                break;
              case '*':
                val = left * right;
                break;
              default:
                break;
            }
            dp[j][i].push_back(val);
          }
        }
      }
    }
  }
  return dp[0][n - 1];
}

vector<int> diffWaysToCompute2(string input) {
  vector<int> output;
  for (int i = 0; i < input.length(); i++) {
    char c = input[i];
    if (c == '+' || c == '-' || c == '*') {
      vector<int> left = diffWaysToCompute2(input.substr(0, i));
      vector<int> right = diffWaysToCompute2(input.substr(i + 1));
      for (const int &l : left) {
        for (const int &r : right) {
          switch (c) {
            case '+':
              output.push_back(l + r);
              break;
            case '-':
              output.push_back(l - r);
              break;
            case '*':
              output.push_back(l * r);
              break;
            default:
              break;
          }
        }
      }
    }
  }
  if (output.empty()) {
    output.push_back(stoi(input));
  }
  return output;
}
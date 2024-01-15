/*
Add strings

题目描述
给定两个由数字组成的字符串，求它们相加的结果。

题解
因为相加运算是从后往前进行的，所以可以先翻转字符串，再逐位计算。这种类型的题考察
的是细节，如进位、位数差等等。
 */
#include <algorithm>
#include <stack>
#include <string>
using namespace std;

string addStrings(string num1, string num2) {
  string output("");

  reverse(num1.begin(), num1.end());
  reverse(num2.begin(), num2.end());

  int oneLen = num1.length(), twoLen = num2.length();
  if (oneLen <= twoLen) {
    swap(num1, num2);
    swap(oneLen, twoLen);
  }

  int addBit = 0;
  for (int i = 0; i < twoLen; ++i) {
    int curSum = (num1[i] - '0') + (num2[i] - '0') + addBit;
    output += to_string((curSum) % 10);
    addBit = curSum < 10 ? 0 : 1;
  }

  for (int i = twoLen; i < oneLen; ++i) {
    int curSum = (num1[i] - '0') + addBit;
    output += to_string((curSum) % 10);
    addBit = curSum < 10 ? 0 : 1;
  }

  if (addBit) {
    output += "1";
  }
  reverse(output.begin(), output.end());
  return output;
}

string addStrings1(string num1, string num2) {
  if (num1.size() == 0) return num2;
  if (num2.size() == 0) return num1;

  int carry = 0;
  int digit = 0;
  int sum = 0;
  stack<char> charStack;

  int i = num1.size() - 1;
  int j = num2.size() - 1;
  while (i >= 0 || j >= 0) {
    sum = 0;
    if (i >= 0) sum += num1[i] - '0';
    if (j >= 0) sum += num2[j] - '0';
    sum += carry;

    digit = sum % 10;
    carry = sum / 10;

    charStack.push(digit + '0');
    --i;
    --j;
  }

  if (carry > 0) charStack.push(carry + '0');

  string res;
  while (!charStack.empty()) {
    res.push_back(charStack.top());
    charStack.pop();
  }

  return res;
}

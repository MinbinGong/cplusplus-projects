/*
 * Add strings
 *
 * Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.
 * 
 * Note:
 * The length of both num1 and num2 is < 5100.
 * Both num1 and num2 contains only digits 0-9.
 * Both num1 and num2 does not contain any leading zero.
 * You must not use any built-in BigInteger library or convert the inputs to integer directly.
 * 
 * Example 1:
 * Input: num1 = "11", num2 = "123"
 * Output: "134"
 * 
 * Example 2:
 * Input: num1 = "456", num2 = "77"
 * Output: "533"
 * 
 * Example 3:
 * Input: num1 = "0", num2 = "0"
 * Output: "0"
 * 
 * Constraints:
 * 1 <= num1.length, num2.length <= 5100
 * num1 and num2 consists of only digits.
 * num1 and num2 does not contain any leading zero except for the zero itself.
 * 
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

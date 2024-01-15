/*
Base 7

题目描述
给定一个十进制整数，求它在七进制下的表示。

题解
进制转换类型的题，通常是利用除法和取模（mod）来进行计算，同时也要注意一些细节，如
负数和零。如果输出是数字类型而非字符串，则也需要考虑是否会超出整数上下界
 */
#include <string>
using namespace std;

string convertToBase7(int n) {
  if (n == 0) {
    return "0";
  }

  bool is_negative = n < 0;
  if (is_negative) {
    n = -n;
  }

  string ans;
  while (n) {
    int a = n / 7, b = n % 7;
    ans = to_string(b) + ans;
    n = a;
  }
  return is_negative ? "-" + ans : ans;
}
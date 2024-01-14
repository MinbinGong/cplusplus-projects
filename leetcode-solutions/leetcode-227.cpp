/*
Basic Calculator

题目描述
给定一个包含加减乘除整数运算的字符串，求其运算结果，只保留整数

题解
如果我们在字符串左边加上一个加号，可以证明其并不改变运算结果，且字符串可以分割成
多个 < 一个运算符，一个数字 > 对子的形式；这样一来我们就可以从左往右处理了。由于乘除的
优先级高于加减，因此我们需要使用一个中间变量来存储高优先度的运算结果。
此类型题也考察很多细节处理，如无运算符的情况，和多个空格的情况等等。
 */
#include <string>
using namespace std;

long parseNum(const string& s, int& i) {
    long n = 0;
    while (i < s.length() && isdigit(s[i])) {
        n = 10 * n + (s[i++] - '0');
    }
    return n;
}

int parseExpr(const string& s, int& i) {
    char op = '+';
    long left = 0, right = 0;
    while (i < s.length()) {
        if (s[i] != ' ') {
            long n = parseNum(s, i);
            switch (op) {
                case '+':
                    left += right;
                    right = n;
                    break;
                case '-':
                    left += right;
                    right = -n;
                    break;
                case '*':
                    right *= n;
                    break;
                default:
                    break;
            }

            if (i < s.length()) {
                op = s[i];
            }
        }
        ++i;
    }
    return left + right;
}

int calculate(string s) {
    int i = 0;
    return parseExpr(s, i);
}
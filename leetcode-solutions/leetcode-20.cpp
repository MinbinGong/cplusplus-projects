/*
Valid Parentheses

题目描述
给定一个只由左右原括号、花括号和方括号组成的字符串，求这个字符串是否合法。合法的
定义是每一个类型的左括号都有一个右括号一一对应，且括号内的字符串也满足此要求。

题解
括号匹配是典型的使用栈来解决的问题。我们从左往右遍历，每当遇到左括号便放入栈内，
遇到右括号则判断其和栈顶的括号是否是统一类型，是则从栈内取出左括号，否则说明字符串不
合法。
 */
#include <stack>
#include <string>

bool isValid(std::string &s) {
    std::stack<char> st;
    for (auto i : s) {
        if (i == '(' || i == '[' || i == '{') {
            st.push(i);
        } else {
            if (st.empty() || (st.top() == '(' && i != ')') || (st.top() == '[' && i != ']') ||
                (st.top() == '{' && i != '}')) {
                return false;
            }
            st.pop();
        }
    }

    return st.empty();
}
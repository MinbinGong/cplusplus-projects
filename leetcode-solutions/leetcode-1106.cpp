/*
 * 1106. Parsing A Boolean Expression
 * 
 * Return the result of evaluating a given boolean expression, represented as a string.
 * 
 * An expression can either be:
 * 
 * "t", evaluating to True;
 * "f", evaluating to False;
 * "!(expr)", evaluating to the logical NOT of the inner expression expr;
 * "&(expr1,expr2,...)", evaluating to the logical AND of 2 or more inner expressions expr1, expr2, ...;
 * "|(expr1,expr2,...)", evaluating to the logical OR of 2 or more inner expressions expr1, expr2, ...
 * 
 * 1 <= expression.length <= 20000
 * expression[i] consists of characters in {'(', ')', '&', '|', '!', 't', 'f', ','}.
 * expression is a valid expression representing a boolean, as given in the description.
 * 
 */
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

class Solution1 {
public:
    bool parseBoolExpr(string expression) {
        int index = 0;
        return dfs(expression, index);
    }
    
private:
    bool dfs(const string& s, int& index) {
        char c = s[index];
        
        // 基础情况：t 或 f
        if (c == 't') {
            index++;
            return true;
        }
        if (c == 'f') {
            index++;
            return false;
        }
        
        // 递归情况：运算符 !、&、|
        if (c == '!') {
            // 跳过 '!' 和 '('
            index += 2;
            bool result = dfs(s, index);
            // 跳过 ')'
            index++;
            return !result;
        }
        
        // & 或 | 运算符
        char op = c;
        // 跳过运算符和 '('
        index += 2;
        
        // 存储所有子表达式的结果
        vector<bool> values;
        
        while (s[index] != ')') {
            if (s[index] == ',') {
                index++;
                continue;
            }
            values.push_back(dfs(s, index));
        }
        
        // 跳过 ')'
        index++;
        
        // 根据运算符计算结果
        if (op == '&') {
            for (bool val : values) {
                if (!val) return false;
            }
            return true;
        } else { // op == '|'
            for (bool val : values) {
                if (val) return true;
            }
            return false;
        }
    }
};

class Solution2 {
public:
    bool parseBoolExpr(string expression) {
        stack<char> st;
        
        for (char c : expression) {
            if (c == ')') {
                // 收集操作数直到遇到 '('
                vector<bool> values;
                while (st.top() != '(') {
                    char top = st.top();
                    st.pop();
                    if (top == 't') values.push_back(true);
                    else if (top == 'f') values.push_back(false);
                }
                st.pop(); // 弹出 '('
                
                // 获取运算符
                char op = st.top();
                st.pop();
                
                // 计算结果
                bool result;
                if (op == '!') {
                    result = !values[0];
                } else if (op == '&') {
                    result = true;
                    for (bool val : values) {
                        if (!val) {
                            result = false;
                            break;
                        }
                    }
                } else { // op == '|'
                    result = false;
                    for (bool val : values) {
                        if (val) {
                            result = true;
                            break;
                        }
                    }
                }
                
                // 将结果压栈
                st.push(result ? 't' : 'f');
            } else if (c != ',') {
                st.push(c);
            }
        }
        
        return st.top() == 't';
    }
};
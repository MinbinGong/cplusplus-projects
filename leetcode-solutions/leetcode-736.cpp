/*
 * Parse Lisp Expression
 *
 * To evaluate the value of an expression, evaluate each sub-expression inside the expression, then apply the function corresponding to the expression to the evaluated sub-expressions.
 * 
 * Note:
 * 1. The given expression expression is guaranteed to be valid.
 * 2. The length of expression is at most 2000.
 * 3. Sub-expressions are separated by spaces.
 * 4. expression only contains letters, digits, '(', ')', '+', '-', '*', and '/'.
 * 5. Variables start with a lowercase letter, then zero or more lowercase letters or digits.
 * 6. The values of variables in the expression are guaranteed to be integers.
 * 7. The values of variables in the expression are guaranteed to be positive integers.
 * 8. The values of variables in the expression are guaranteed to be non-negative integers.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>
using namespace std;

class Solution {
public:
    int evaluate(string expression) {
        vector<string> tokens = tokenize(expression);
        int pos = 0;
        unordered_map<string, int> scope;
        return eval(tokens, pos, scope);
    }

private:
    vector<string> tokenize(const string& s) {
        vector<string> res;
        int i = 0, n = s.size();
        while (i < n) {
            if (s[i] == ' ') {
                i++;
                continue;
            }
            if (s[i] == '(' || s[i] == ')') {
                res.push_back(string(1, s[i]));
                i++;
            } else {
                int start = i;
                if (isdigit(s[i]) || s[i] == '-') {
                    i++;
                    while (i < n && isdigit(s[i])) i++;
                } else {
                    while (i < n && isalpha(s[i])) i++;
                }
                res.push_back(s.substr(start, i - start));
            }
        }
        return res;
    }

    int eval(vector<string>& tokens, int& pos, unordered_map<string, int> scope) {
        string token = tokens[pos];
        if (token == "(") {
            pos++; // skip '('
            string op = tokens[pos++];
            if (op == "let") {
                // let: (let v1 e1 v2 e2 ... vn en expr)
                while (true) {
                    string cur = tokens[pos];
                    if (cur == "(") {
                        // start of final expression
                        int res = eval(tokens, pos, scope);
                        pos++; // skip closing ')'
                        return res;
                    } else if (isdigit(cur[0]) || (cur[0] == '-' && cur.size() > 1)) {
                        // final expression is a number
                        int res = stoi(cur);
                        pos++;
                        pos++; // skip ')'
                        return res;
                    } else {
                        // variable or binding
                        // look ahead to decide
                        if (tokens[pos + 1] == ")") {
                            // final expression: variable
                            int res = scope.at(cur);
                            pos++;
                            pos++; // skip ')'
                            return res;
                        } else {
                            // binding: var value
                            string var = cur;
                            pos++;
                            int val = eval(tokens, pos, scope);
                            scope[var] = val;
                        }
                    }
                }
            } else if (op == "add" || op == "mult") {
                int e1 = eval(tokens, pos, scope);
                int e2 = eval(tokens, pos, scope);
                pos++; // skip closing ')'
                return (op == "add") ? e1 + e2 : e1 * e2;
            }
            // unreachable
            return 0;
        } else {
            // atom: number or variable
            pos++;
            if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
                return stoi(token);
            } else {
                return scope.at(token);
            }
        }
    }
};
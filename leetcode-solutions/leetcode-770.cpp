/*
 * 770. Basic Calculator IV
 *
 * Given an expression such as expression = "e + 8 - a + 5" and an evaluation map such as {"e": 1} (given in terms of evalvars = ["e"] and evalints = [1]), return a list of tokens representing the simplified expression, such as ["-1*a","14"]
 * 
 * An expression alternates chunks and symbols, with a space separating each chunk and symbol.
 * A chunk is either an expression in parentheses, a variable, or a non-negative integer.
 * A variable is a string of lowercase letters (not including digits.) Note that variables can be multiple letters, and note that variables never have a leading coefficient or unary operator like "2x" or "-x".
 * Expressions are evaluated in the usual order: brackets first, then multiplication, then addition and subtraction. For example, expression = "1 + 2 * 3" has an answer of ["7"].
 * 
 * The format of the output is as follows:
 * 1. For terms with leading coefficients, the coefficient comes first, then the operator.
 * 2. Terms with leading coefficients of 1 should be ignored.
 * 3. If a term has a constant term, it should be put in the last position.
 * 4. Terms (including constant terms) with coefficient 0 should be ignored.
 * 
 * Note:
 * 1. The given expression is well-formed: there are no leading or trailing spaces, no parentheses nested inside other parentheses, and no misaligned spaces.
 * 2. The expression does not contain leading coefficients or unary operators like "2x" or "-x".
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        // 1. 构造变量映射表
        for (int i = 0; i < evalvars.size(); ++i) {
            mp[evalvars[i]] = evalints[i];
        }

        // 2. 初始化解析器并开始解析
        str = expression;
        index = 0;
        token = get_token();

        vector<string> res = exp();

        // 3. 过滤掉系数为0的项（在merge_factor中已做）
        return res;
    }

private:
    string token;                       // 当前解析的 token
    string str;                          // 整个表达式
    int index;                            // 解析位置
    unordered_map<string, int> mp;        // 变量名 -> 数值

    // ---------- 工具函数 ----------
    string get_token() {
        while (index < str.size() && str[index] == ' ') ++index;   // 跳过空格
        if (index >= str.size()) return "";

        if (isdigit(str[index])) {        // 数字
            string num;
            while (index < str.size() && isdigit(str[index])) num += str[index++];
            return num;
        }
        else if (islower(str[index])) {   // 变量（题目保证只有小写字母）
            string var;
            while (index < str.size() && islower(str[index])) var += str[index++];
            return var;
        }
        else {                            // 运算符或括号
            string op;
            op += str[index++];
            return op;
        }
    }

    bool is_number(const string& s) {
        for (char c : s) if (c < '0' || c > '9') return false;
        return true;
    }

    // 分离因子：如 "3*a*b" 分离出系数 "3" 和变量串 "a*b"
    void split_factor(const string& fac, string& coeff, string& vars) {
        size_t pos = fac.find('*');
        if (pos == string::npos) {
            coeff = fac;
            vars = "";
        } else {
            coeff = fac.substr(0, pos);
            vars = fac.substr(pos + 1);
        }
    }

    // 两个因子相乘：如 "3*a*b" 和 "2*b*c" -> "6*a*b*b*c"
    string multiply(const string& a, const string& b) {
        string coeff1, vars1, coeff2, vars2;
        split_factor(a, coeff1, vars1);
        split_factor(b, coeff2, vars2);

        int c = stoi(coeff1) * stoi(coeff2);
        string res = to_string(c);

        // 合并变量部分
        vector<string> v1, v2;
        if (!vars1.empty()) {
            size_t pos = 0, next;
            while ((next = vars1.find('*', pos)) != string::npos) {
                v1.push_back(vars1.substr(pos, next - pos));
                pos = next + 1;
            }
            v1.push_back(vars1.substr(pos));
        }
        if (!vars2.empty()) {
            size_t pos = 0, next;
            while ((next = vars2.find('*', pos)) != string::npos) {
                v2.push_back(vars2.substr(pos, next - pos));
                pos = next + 1;
            }
            v2.push_back(vars2.substr(pos));
        }

        // 合并、排序
        vector<string> allVars;
        allVars.insert(allVars.end(), v1.begin(), v1.end());
        allVars.insert(allVars.end(), v2.begin(), v2.end());
        sort(allVars.begin(), allVars.end());

        for (const string& var : allVars) {
            res += "*" + var;
        }
        return res;
    }

    // 自定义排序：先按度降序，度相同按变量串字典序升序
    static bool cmp_term(const string& s1, const string& s2) {
        int deg1 = count(s1.begin(), s1.end(), '*');
        int deg2 = count(s2.begin(), s2.end(), '*');
        if (deg1 != deg2) return deg1 > deg2;

        // 度相同，比较变量部分（忽略系数）
        string vars1 = (s1.find('*') == string::npos) ? "" : s1.substr(s1.find('*') + 1);
        string vars2 = (s2.find('*') == string::npos) ? "" : s2.substr(s2.find('*') + 1);
        return vars1 < vars2;
    }

    // 合并同类项：输入 terms，返回合并后并过滤掉系数0的项
    vector<string> merge_terms(vector<string>& terms) {
        if (terms.empty()) return {};
        sort(terms.begin(), terms.end(), cmp_term);

        vector<string> res;
        string coeff, vars;
        split_factor(terms[0], coeff, vars);
        int sum = stoi(coeff);

        for (size_t i = 1; i < terms.size(); ++i) {
            string c, v;
            split_factor(terms[i], c, v);
            if (v == vars) {
                sum += stoi(c);
            } else {
                if (sum != 0) {
                    string term = to_string(sum);
                    if (!vars.empty()) term += "*" + vars;
                    res.push_back(term);
                }
                coeff = c;
                vars = v;
                sum = stoi(coeff);
            }
        }
        if (sum != 0) {
            string term = to_string(sum);
            if (!vars.empty()) term += "*" + vars;
            res.push_back(term);
        }
        return res;
    }

    // ---------- 递归下降解析 ----------
    vector<string> exp() {
        vector<string> left = additive();
        vector<string> temp;

        while (token == "+" || token == "-") {
            string op = token;
            token = get_token();               // 吃掉运算符
            vector<string> right = additive();

            if (op == "+") {
                left.insert(left.end(), right.begin(), right.end());
            } else {
                // 减法：将 right 每一项乘以 -1
                for (string& s : right) {
                    string coeff, vars;
                    split_factor(s, coeff, vars);
                    int c = -stoi(coeff);
                    s = to_string(c);
                    if (!vars.empty()) s += "*" + vars;
                }
                left.insert(left.end(), right.begin(), right.end());
            }
        }

        return merge_terms(left);
    }

    vector<string> additive() {
        vector<string> left = factor();
        vector<string> temp;

        while (token == "*") {
            token = get_token();               // 吃掉 '*'
            vector<string> right = factor();

            temp.clear();
            for (const string& a : left) {
                for (const string& b : right) {
                    temp.push_back(multiply(a, b));
                }
            }
            left = temp;
        }
        return left;
    }

    vector<string> factor() {
        vector<string> res;
        if (token == "(") {
            token = get_token();                // 吃掉 '('
            res = exp();
            token = get_token();                // 吃掉 ')'
        }
        else if (is_number(token)) {
            res.push_back(token);               // 纯数字项
            token = get_token();
        }
        else {
            // 变量：先查是否在 eval 映射中
            if (mp.count(token)) {
                res.push_back(to_string(mp[token]));
            } else {
                res.push_back("1*" + token);    // 变量项统一格式：系数*变量名
            }
            token = get_token();
        }
        return res;
    }
};
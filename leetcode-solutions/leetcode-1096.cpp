/**
 * 1096. Brace Expansion II
 * Hard
 * 
 * (This problem is an interactive problem.)
 * 
 * Under the grammar given below, strings can represent a set of lowercase words. Let R(expr) denote the set of words the expression represents.
 * 
 * The grammar can best be understood through simple examples:
 * 
 * Single letters represent a singleton set containing that word.
 * R("a") = {"a"}
 * R("w") = {"w"}
 * When we take a comma-delimited list of two or more expressions, we take the union of possibilities.
 * R("{a,b,c}") = {"a","b","c"}
 * R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each word at most once)
 * When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression and the second word comes from the second expression.
 * R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
 * 
 * Example 1:
 * Input: expression = "{a,b}{c,{d,e}}"
 * Output: ["ac","ad","ae","bc","bd","be"]
 * 
 * Example 2:
 * Input: expression = "{{a,z},a{b,c},{ab,z}}"
 * Output: ["a","ab","ac","z"]
 * 
 * Note:
 * 1 <= expression.length <= 60
 * expression[i] consists of '{', '}', ','or lowercase English letters.
 * The given expression represents a set of words based on the grammar given in the description.
 * 
 */
#include <vector>
#include <set>
#include <string>
using namespace std;

class Solution1 {
public:
    vector<string> braceExpansionII(string expression) {
        int pos = 0;
        auto res = parseExpr(expression, pos);
        return vector<string>(res.begin(), res.end());
    }
    
private:
    // 解析表达式：处理并集（逗号分隔）
    set<string> parseExpr(const string& s, int& pos) {
        set<string> result;
        while (true) {
            // 解析一个项（可能是字母或花括号内的内容）
            auto termSet = parseTerm(s, pos);
            
            // 合并当前项到结果中（笛卡尔积）
            result = merge(result, termSet);
            
            // 如果遇到文件结尾或右花括号，返回结果
            if (pos >= s.size() || s[pos] == '}') {
                break;
            }
            // 如果是逗号，跳过并继续处理下一项
            if (s[pos] == ',') {
                pos++;
                continue;
            }
        }
        return result;
    }
    
    // 解析项：处理拼接（相邻项直接合并）
    set<string> parseTerm(const string& s, int& pos) {
        set<string> result = {""};
        while (pos < s.size() && s[pos] != ',' && s[pos] != '}') {
            auto factorSet = parseFactor(s, pos);
            // 笛卡尔积：将当前因子与之前的结果组合
            set<string> newResult;
            for (const auto& left : result) {
                for (const auto& right : factorSet) {
                    newResult.insert(left + right);
                }
            }
            result = move(newResult);
        }
        return result;
    }
    
    // 解析因子：字母序列或花括号内的表达式
    set<string> parseFactor(const string& s, int& pos) {
        set<string> result;
        if (isalpha(s[pos])) {
            // 连续字母
            string word;
            while (pos < s.size() && isalpha(s[pos])) {
                word += s[pos++];
            }
            result.insert(word);
        } else if (s[pos] == '{') {
            // 花括号内的表达式
            pos++; // 跳过 '{'
            result = parseExpr(s, pos);
            pos++; // 跳过 '}'
        }
        return result;
    }
    
    // 合并两个集合：A + B 的笛卡尔积
    set<string> merge(const set<string>& a, const set<string>& b) {
        if (a.empty()) return b;
        set<string> result;
        for (const auto& left : a) {
            for (const auto& right : b) {
                result.insert(left + right);
            }
        }
        return result;
    }
};

class Solution2 {
public:
    vector<string> braceExpansionII(string expression) {
        stack<set<string>> nums;  // 操作数栈
        stack<char> ops;           // 运算符栈
        
        int n = expression.size();
        for (int i = 0; i < n; i++) {
            char c = expression[i];
            
            if (isalpha(c)) {
                // 处理连续字母
                if (i > 0 && (expression[i-1] == '}' || isalpha(expression[i-1]))) {
                    // 前一个字符是字母或 '}'，说明需要隐式乘法
                    ops.push('*');
                }
                string word;
                while (i < n && isalpha(expression[i])) {
                    word += expression[i++];
                }
                i--;
                nums.push({word});
            }
            else if (c == '{') {
                if (i > 0 && (expression[i-1] == '}' || isalpha(expression[i-1]))) {
                    ops.push('*');
                }
                ops.push('{');
            }
            else if (c == ',') {
                // 逗号优先级最低，先计算所有乘法
                while (!ops.empty() && ops.top() == '*') {
                    eval(nums, ops);
                }
                ops.push('+');
            }
            else if (c == '}') {
                // 计算直到遇到 '{'
                while (ops.top() != '{') {
                    eval(nums, ops);
                }
                ops.pop(); // 弹出 '{'
            }
        }
        
        while (!ops.empty()) {
            eval(nums, ops);
        }
        
        set<string> resultSet = nums.top();
        return vector<string>(resultSet.begin(), resultSet.end());
    }
    
private:
    void eval(stack<set<string>>& nums, stack<char>& ops) {
        char op = ops.top(); ops.pop();
        auto b = nums.top(); nums.pop();
        auto a = nums.top(); nums.pop();
        
        if (op == '+') {
            // 并集
            a.insert(b.begin(), b.end());
            nums.push(a);
        } else if (op == '*') {
            // 笛卡尔积
            set<string> result;
            for (const auto& x : a) {
                for (const auto& y : b) {
                    result.insert(x + y);
                }
            }
            nums.push(result);
        }
    }
};
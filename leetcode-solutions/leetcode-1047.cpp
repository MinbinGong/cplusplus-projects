/*
 * 1047. Remove All Adjacent Duplicates In String
 *
 * Given a string S of lowercase letters, a duplicate removal consists of choosing two adjacent and equal letters, and removing them.
 * 
 * We repeatedly make duplicate removals on S until we no longer can.
 * 
 * Return the final string after all such duplicate removals have been made.  It is guaranteed the answer is unique.
 * 
 * Example 1:
 * Input: "abbaca"
 * Output: "ca"
 * Explanation: 
 * We can remove "bb" from "abbaca" to yield "aaca", then we can remove "aa" from "aaca" to yield "ca".
 * 
 * Example 2:
 * Input: "azxxzy"
 * Output: "ay"
 * 
 * Note:
 * 1. 1 <= S.length <= 20000
 * 2. S consists only of English lowercase letters.
 * 
 */
#include <string>
#include <stack>
using namespace std;

class Solution1 {
public:
    // 方法1：使用栈（最直观）
    string removeDuplicates(string s) {
        stack<char> st;
        
        for (char c : s) {
            if (!st.empty() && st.top() == c) {
                st.pop();  // 发现相邻重复，弹出栈顶
            } else {
                st.push(c); // 否则压入栈中
            }
        }
        
        // 将栈中字符构建成结果字符串
        string result;
        while (!st.empty()) {
            result = st.top() + result; // 注意顺序，栈是后进先出
            st.pop();
        }
        
        return result;
    }
};

class Solution2 {
public:
    // 方法2：使用字符串模拟栈（更高效，避免反转操作）
    string removeDuplicates(string s) {
        string result; // 用字符串作为栈
        
        for (char c : s) {
            if (!result.empty() && result.back() == c) {
                result.pop_back(); // 发现相邻重复，弹出最后一个字符
            } else {
                result.push_back(c); // 否则添加字符
            }
        }
        
        return result;
    }
};

class Solution3 {
public:
    string removeDuplicates(string s) {
        int write = 0; // 写指针
        
        for (int read = 0; read < s.size(); read++) {
            if (write > 0 && s[write - 1] == s[read]) {
                write--; // 发现重复，回退写指针
            } else {
                s[write++] = s[read]; // 写入当前字符
            }
        }
        
        s.resize(write); // 调整字符串大小
        return s;
    }
};